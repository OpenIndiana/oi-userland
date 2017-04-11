
COMPONENTS+= xorg-server
COMPONENTS+= $(X11_GATE_INSTALL_ACTION)

COMPONENTS+= tigervnc
COMPONENTS+= $(X11_GATE_INSTALL_ACTION)

# driver
COMPONENTS+= xf86-input-keyboard
COMPONENTS+= xf86-input-mouse
COMPONENTS+= xf86-input-void
COMPONENTS+= xf86-video-ast
COMPONENTS+= xf86-video-mga
COMPONENTS+= xf86-video-dummy		
COMPONENTS+= xf86-input-acecad
COMPONENTS+= xf86-input-synaptics
COMPONENTS+= xf86-input-vmmouse
COMPONENTS+= xf86-input-hotkey
COMPONENTS+= xf86-video-ati
COMPONENTS+= xf86-video-cirrus
COMPONENTS+= xf86-video-intel
COMPONENTS+= xf86-video-mach64
COMPONENTS+= xf86-video-nv
COMPONENTS+= xf86-video-openchrome
COMPONENTS+= xf86-video-r128
COMPONENTS+= xf86-video-savage
COMPONENTS+= xf86-video-trident
COMPONENTS+= xf86-video-vesa
COMPONENTS+= xf86-video-vmware
COMPONENTS+= ../meta-packages/xorg-video
COMPONENTS+= $(X11_GATE_INSTALL_ACTION)
