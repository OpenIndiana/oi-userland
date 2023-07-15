@Library("BuildLib") _
pipeline {
    agent {
        node {
            label 'illumos-gate'
        }
    }
    stages {
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
                withPublisher('openindiana.org', 'full') {
                    sh 'gmake setup'
                }
            }
        }
        stage('build illumos-gate') {
            steps {
                withPublisher('openindiana.org', 'incremental') {
                    dir('components/openindiana/illumos-gate') {
                        sh 'gmake publish'
                    }
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

