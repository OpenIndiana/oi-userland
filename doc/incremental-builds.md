# Incremental builds

oi-userland supports incremental builds. They can be activated by setting the **BASS_O_MATIC_MODE** environment variable to _incremental_.

## Implementation
Implementation is rather very simple and relies on a fact that every time a component is modified, the Makefile has to be changed and commited. For detecting changes we rely on _git_ and we try to guess the initial commit to look at. By default we scan the **GIT_PREVIOUS_SUCCESSFUL_COMMIT** environment variable (set by default in Jenkins environments): if the variable is not found, bass-o-matic defaults to 'HEAD~1'.