// OpenIndiana Userland Jenkinsfile, (c) 2021 Olaf Bohlen <olbohlen@eenfach.de>
// OpenIndiana Userland Jenkinsfile, (c) 2021 Till Wegmueller <toasterson@gmail.com>

// ensure the jenkins user can modify SMF services, e.g. run:
// usermod -A solaris.smf.* -P 'Service Operator' jenkins

// To add more things have a look at the documentation under
// https://github.com/jenkinsci/pipeline-github-plugin

// TODO: Do not build draft PR's
// TODO: Figure out what to do when no Makefile was changed
// TODO: have two build Jobs (one for oi/hipster and another for this PR)
// TODO: matrix build against multiple configuration gcc-7, gcc-10, gcc-11 and encumbered vs. without encumbered

pipeline {
    options {
        // set a timeout of 600 minutes for this pipeline
        timeout(time: 600, unit: 'MINUTES')
    }
    agent {
      node {
        label 'buildserver'
      }
    }
    stages {
        stage('setup stage') {
            steps {
		        sh './tools/jenkinshelper.ksh -s setup'
            }
        }

        stage('build changed components') {
            steps {
                sh './tools/jenkinshelper.ksh -s build_changed'
            }
        }

	    stage('create initial pkgdepotd.conf if not exists') {
    	    steps {
                sh './tools/jenkinshelper.ksh -s prepare_pkgdepotd'
	          }
	    }

        stage('cleanup') {
            when {
                changeRequest()
            }
            steps {
                script {
                    if (pullRequest.state == "closed" || pullRequest.merged) {
                        sh './tools/jenkinshelper.ksh -s cleanup_pr'
                    }
                }
            }
        }
    }
}

