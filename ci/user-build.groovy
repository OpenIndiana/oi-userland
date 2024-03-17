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

@NonCPS
String getChangedFilesList() {
    changedFiles = []
    for (changeLogSet in currentBuild.changeSets) {
        for (entry in changeLogSet.getItems()) { // for each commit in the detected changes
            for (file in entry.getAffectedFiles()) {
                changedFiles.add(file.getPath()) // add changed file to list
            }
        }
    }
    return changedFiles
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
                        writeFile file: 'changed_files.txt', text: getChangedFilesList().join("\n")
                    }
                    sh './tools/jenkinshelper-main.ksh -s build_changed'
                }
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

