@Library("BuildLib") _
pipeline {
    agent {
        node {
            label 'encumbered'
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
                withPublisher('hipster-encumbered', 'incremental') {
                    ignoreEncumberedComponents(['audacity', 'gsm', 'gst-plugins-bad', 'rtmpdump'])
                    sh 'rm -f components/encumbered/components.mk'
                    sh 'rm -f components/encumbered/depends.mk'
                    sh 'gmake -C components/encumbered setup'
                }
            }
        }
        stage('build encumbered packages') {
            steps {
                withPublisher('hipster-encumbered', 'incremental') {
                    sh 'gmake -C components/encumbered publish -k'
                }
            }
        }
        stage('update system') {
            steps {
                update()
            }
        }
    }
}

