import jenkins.model.Jenkins

@Library("BuildLib") _

/**
 * Gets the commit hash from a Jenkins build object, if any
 */
@NonCPS
def commitHashForBuild( build ) {
  def scmAction = build?.actions.find { action -> action instanceof jenkins.scm.api.SCMRevisionAction }
  return scmAction?.revision?.hash
}

pipeline {
    agent {
        node {
            label 'userland'
        }
    }
    stages {
        stage('Ensure is ready to build') {
            steps {
                sh 'pfexec /usr/sbin/mountall -F nfs || exit 0'
            }
        }
        stage('Git Checkout') {
            steps {
                withSharedWs() {
                    git branch: 'oi/hipster', url: 'https://github.com/OpenIndiana/oi-userland.git'
                }
            }
        }
        stage('Gmake Setup') {
            steps {
                sh 'rm -f components/components.mk'
                sh 'rm -f components/depends.mk'
                withPublisher('openindiana.org', 'incremental') {
                    sh 'gmake setup'
                }
            }
        }
        stage('Gmake Publish') {
            steps {
                withPublisher('openindiana.org', 'incremental') {
                    script {
                        def last_build = Jenkins.instance.getItem('OpenIndiana').getItem('Userland').lastSuccessfulBuild
                        def last_commit = commitHashForBuild(last_build)
                    
                    }
                    sh './tools/jenkinshelper-main.ksh -s build_changed'
                }
            }
        }
        stage('copy packages') {
            steps {
                pkgcopy()
            }
        }
        stage('update system') {
            steps {
                update()
                sh '/opt/local/bin/cleanup_bootenvs.sh'
            }
        }
    }
}

