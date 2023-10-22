import jenkins.model.Jenkins

@Library("BuildLib") _

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
                        def last_commit = Jenkins.instance.getItem('Userland').lastSuccessfulBuild.changeset[0].revision
                    }
                    sh './tools/jenkinshelper-main.ksh -s build_changed $last_commit'
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

