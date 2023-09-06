@Library("BuildLib") _
pipeline {
    agent {
        node {
            label 'userland'
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
        stage('Gmake Publish') {
            steps {
                withPublisher('openindiana.org', 'full') {
                    sh 'gmake publish -k'
                }
            }
        }
    }
}

