pipeline {
  agent any
  options {
    timeout(time: 1, unit: 'HOURS')
  }

  stages {
    stage("Check out") {
      steps {
        cleanWs()
        checkout scm
      }
    }

    stage('Prepare build zone') {
      steps {
        sh '/usr/bin/pfexec. ./tools/userland-zone spawn-zone --id ' + env.CHANGE_ID
      }
    }

    stage('Destroy build zone') {
      steps {
        sh '/usr/bin/pfexec ./tools/userland-zone destroy-zone --id ' + env.CHANGE_ID
      }
    }
  }
}
