// OpenIndiana Userland Jenkinsfile, (c) 2021 Olaf Bohlen <olbohlen@eenfach.de>

// ensure the jenkins user can modify SMF services, e.g. run:
// usermod -A solaris.smf.* -P 'Service Operator' jenkins

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
    }
}

