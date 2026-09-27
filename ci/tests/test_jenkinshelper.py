#!/usr/bin/env python3
"""Exercise PR component selection with real Git history and stubbed builds."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

HELPER = Path(__file__).resolve().parents[2] / 'tools/jenkinshelper.ksh'


class ComponentSelection(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.env = dict(os.environ, GIT_CONFIG_NOSYSTEM='1',
                        GIT_CONFIG_GLOBAL=os.devnull, CHANGE_ID='123',
                        CHANGE_TARGET='oi/hipster')
        self.git('init', '-q')
        self.git('config', 'user.name', 'CI test')
        self.git('config', 'user.email', 'ci@example.invalid')
        self.write('components/runtime/unrelated/Makefile', 'base\n')
        self.commit('base')
        self.base = self.git('rev-parse', 'HEAD')
        self.git('update-ref', 'refs/remotes/origin/oi/hipster', self.base)
        self.write('components/sysutils/pr/Makefile', 'PR\n')
        self.commit('PR component')
        self.head = self.git('rev-parse', 'HEAD')
        self.git('update-ref', 'refs/remotes/origin/PR-123', self.head)
        bindir = self.root / 'bin'
        bindir.mkdir()
        self.write('bin/gmake', '#!/bin/sh\nprintf "%s %s\\n" "$PWD" "$*" >> "$BUILD_LOG"\nexit "${BUILD_EXIT:-0}"\n')
        self.write('bin/psrinfo', '#!/bin/sh\necho 2\n')
        for path in bindir.iterdir():
            path.chmod(0o755)
        self.env['PATH'] = str(bindir) + os.pathsep + os.environ['PATH']
        self.env['BUILD_LOG'] = str(self.root / 'build.log')

    def git(self, *args):
        return subprocess.check_output(['git', *args], cwd=self.root,
                                       env=self.env, text=True).strip()

    def write(self, path, contents):
        path = self.root / path
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(contents)

    def commit(self, message):
        self.git('add', 'components')
        self.git('commit', '-qm', message)

    def run_helper(self):
        return subprocess.run([os.environ.get('KSH', '/bin/ksh'), str(HELPER),
                               '-s', 'build_changed'], cwd=self.root,
                              env=self.env, text=True, capture_output=True)

    def assert_only_pr(self):
        result = self.run_helper()
        self.assertEqual(result.returncode, 0, result.stderr)
        lines = (self.root / 'build.log').read_text().splitlines()
        self.assertEqual(len(lines), 2, lines)
        self.assertTrue(all('/components/sysutils/pr ' in x for x in lines), lines)

    def advance_target(self):
        self.git('checkout', '-q', '--detach', self.base)
        self.write('components/runtime/unrelated/Makefile', 'target update\n')
        self.commit('unrelated target update')
        target = self.git('rev-parse', 'HEAD')
        self.git('update-ref', 'refs/remotes/origin/oi/hipster', target)
        self.git('checkout', '-q', '--detach', self.head)
        return target

    def test_head_checkout_target_advanced(self):
        self.advance_target()
        self.assert_only_pr()

    def test_merge_checkout_target_moves_after_merge(self):
        target = self.advance_target()
        self.git('merge', '--no-ff', '-qm', 'Jenkins merge', target)
        merged = self.git('rev-parse', 'HEAD')
        self.git('checkout', '-q', '--detach', target)
        self.write('components/runtime/unrelated/Makefile', 'later target update\n')
        self.commit('target moves after Jenkins selects merge revision')
        self.git('update-ref', 'refs/remotes/origin/oi/hipster', 'HEAD')
        self.git('checkout', '-q', '--detach', merged)
        self.assert_only_pr()

    def test_merge_checkout(self):
        target = self.advance_target()
        self.git('merge', '--no-ff', '-qm', 'Jenkins merge', target)
        self.assert_only_pr()

    def test_missing_target_fails_before_build(self):
        self.git('update-ref', '-d', 'refs/remotes/origin/oi/hipster')
        self.assertNotEqual(self.run_helper().returncode, 0)
        self.assertFalse((self.root / 'build.log').exists())

    def test_missing_pr_head_fails_before_build(self):
        self.git('update-ref', '-d', 'refs/remotes/origin/PR-123')
        self.assertNotEqual(self.run_helper().returncode, 0)
        self.assertFalse((self.root / 'build.log').exists())

    def test_build_failure_is_preserved(self):
        self.env['BUILD_EXIT'] = '7'
        self.assertEqual(self.run_helper().returncode, 7)

    def test_unmerged_pr_head_fails_before_build(self):
        self.write('components/sysutils/pr/Makefile', 'new PR head\n')
        self.commit('new head')
        self.git('update-ref', 'refs/remotes/origin/PR-123', 'HEAD')
        self.git('checkout', '-q', '--detach', self.head)
        self.assertNotEqual(self.run_helper().returncode, 0)
        self.assertFalse((self.root / 'build.log').exists())

    def test_no_component_changes(self):
        self.git('checkout', '-q', '--detach', self.base)
        self.write('components/README', 'documentation\n')
        self.commit('documentation only')
        self.git('update-ref', 'refs/remotes/origin/PR-123', 'HEAD')
        self.assertEqual(self.run_helper().returncode, 0)
        self.assertFalse((self.root / 'build.log').exists())

    def test_deleted_and_non_component_makefiles_are_not_built(self):
        self.git('rm', 'components/runtime/unrelated/Makefile')
        self.write('components/Makefile', 'aggregate\n')
        self.write('components/sysutils/pr/Makefile.backup', 'backup\n')
        self.commit('remove component and change aggregate')
        self.git('update-ref', 'refs/remotes/origin/PR-123', 'HEAD')
        self.assert_only_pr()

    def test_change_target_is_respected(self):
        self.git('update-ref', 'refs/remotes/origin/other/target', self.base)
        self.git('update-ref', '-d', 'refs/remotes/origin/oi/hipster')
        self.env['CHANGE_TARGET'] = 'other/target'
        self.assert_only_pr()

    def test_branch_checkout_without_pr_metadata(self):
        self.env.pop('CHANGE_ID')
        self.env.pop('CHANGE_TARGET')
        self.advance_target()
        self.assert_only_pr()


if __name__ == '__main__':
    unittest.main()
