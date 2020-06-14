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
        sh './tools/userland-zone spawn-zone --id ' + env.CHANGE_ID
      }
    }

    stage('Destroy build zone') {
      steps {
        sh './tools/userland-zone destroy-zone --id ' + env.CHANGE_ID
      }
    }
  }
}
