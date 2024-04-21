# dwl - dwm for Wayland

Join us on our IRC channel: [#dwl on Libera Chat]  
Or on our [Discord server].

dwl is a compact, hackable compositor for [Wayland] based on [wlroots]. It is
intended to fill the same space in the Wayland world that dwm does in X11,
primarily in terms of functionality, and secondarily in terms of philosophy.
Like dwm, dwl is:

- Easy to understand, hack on, and extend with patches
- One C source file (or a very small number) configurable via `config.h`
- Tied to as few external dependencies as possible

dwl is not meant to provide every feature under the sun. Instead, like dwm, it
sticks to features which are necessary, simple, and straightforward to implement
given the base on which it is built. Implemented default features are:

- Any features provided by dwm/Xlib: simple window borders, tags, keybindings,
  client rules, mouse move/resize. Providing a built-in status bar is an
  exception to this goal, to avoid dependencies on font rendering and/or
  drawing libraries when an external bar could work well.
- Configurable multi-monitor layout support, including position and rotation
- Configurable HiDPI/multi-DPI support
- Idle-inhibit protocol which lets applications such as mpv disable idle
  monitoring
- Provide information to external status bars via stdout/stdin
- Urgency hints via xdg-activate protocol
- Support screen lockers via ext-session-lock-v1 protocol
- Various Wayland protocols
- XWayland support as provided by wlroots (can be enabled in `config.mk`)
- Zero flickering - Wayland users naturally expect that "every frame is perfect"
- Layer shell popups (used by Waybar)
- Damage tracking provided by scenegraph API

Given the Wayland architecture, dwl has to implement features from dwm **and**
the xorg-server. Because of this, it is impossible to maintain the original
project goal of 2000 SLOC and have a reasonably complete compositor with
features comparable to dwm. However, this does not mean that the code will grow
indiscriminately. We will try to keep the code as small as possible.

Features under consideration (possibly as patches) are:

- Protocols made trivial by wlroots
- Implement the text-input and input-method protocols to support IME once ibus
  implements input-method v2 (see https://github.com/ibus/ibus/pull/2256 and
  https://codeberg.org/dwl/dwl/pulls/235)

Feature *non-goals* for the main codebase include:

- Client-side decoration (any more than is necessary to tell the clients not to)
- Client-initiated window management, such as move, resize, and close, which can
  be done through the compositor
- Animations and visual effects

## About this fork

A number of patches are applied here:

- alwayscenter
- autostart
- bar
- genericgaps
- ipc-clipboard-patch
- snail
- movestack
- pertag

It is also configured to fit my system (which means that some of the commands it
loads are scripts on my local folder).

I strongly suggest that you fork upstream and pick the patches that interest you
instead of using this repo.

### Additional dependencies

The following dependencies are used for keybindings and autostart:

- [foot](https://codeberg.org/dnkl/foot): Terminal emulator
- [wmenu](https://git.sr.ht/~adnano/wmenu): Dmenu replacement for wayland
- [wmenu_drun](https://github.com/denisdubochevalier/wmenu_drun): Port of dmenu_drun for wayland and wmenu
- [ytfzf-wmenu](https://github.com/denisdubochevalier/ytfzf-wmenu): Fork of ytfzf to watch youtube with wmenu
- [swaylock](https://github.com/swaywm/swaylock): Screen locker
- [notes-sh](https://github.com/denisdubochevalier/notes-sh): Script to navigate markdown notes with wmenu
- [wradio](https://github.com/denisdubochevalier/wradio): Script to launch web radios
- [grim](https://github.com/emersion/grim): Screenshot tool
- [wlogout](https://github.com/ArtsyMacaw/wlogout): Logout menu for wayland environments
- [qutebrowser](https://github.com/qutebrowser/qutebrowser): Vim-like browser
- [volumecontrol](https://github.com/denisdubochevalier/volumecontrol): Script to control devices volume
- [resetxdgportal](https://github.com/denisdubochevalier/resetxdgportal): Script to reset XDG portals on startup
- [dbus](https://wiki.freedesktop.org/www/Software/dbus/): D-Bus message bus
- [systemd](https://systemd.io/): Used for environment importing
- [polkitkdeauth](https://github.com/denisdubochevalier/polkitkdeauth): Script to authenticate using polkit-kde
- [dunst](https://github.com/dunst-project/dunst): Notification daemon
- [wl-clipboard](https://github.com/bugaevc/wl-clipboard): Clipboard utilities
- [swaybg](https://github.com/swaywm/swaybg): Wallpaper utility
- [glib2](https://docs.gtk.org/glib/): For the gsettings utility to set GTK theme

## Building dwl

dwl has the following dependencies:
```
libinput
wayland
wlroots (compiled with the libinput backend)
xkbcommon
wayland-protocols (compile-time only)
pkg-config (compile-time only)
```
If you enable X11 support:
```
libxcb
libxcb-wm
wlroots (compiled with X11 support)
Xwayland (runtime only)
```

Simply install these (and their `-devel` versions if your distro has separate
development packages) and run `make`.  If you wish to build against a Git
version of wlroots, check out the [wlroots-next branch].

To enable XWayland, you should uncomment its flags in `config.mk`.

## Configuration

All configuration is done by editing `config.h` and recompiling, in the same
manner as dwm. There is no way to separately restart the window manager in
Wayland without restarting the entire display server, so any changes will take
effect the next time dwl is executed.

As in the dwm community, we encourage users to share patches they have created.
Check out the dwl [patches repository] and [patches wiki]!

## Running dwl

dwl can be run on any of the backends supported by wlroots. This means you can
run it as a separate window inside either an X11 or Wayland session, as well
as directly from a VT console. Depending on your distro's setup, you may need
to add your user to the `video` and `input` groups before you can run dwl on
a VT. If you are using `elogind` or `systemd-logind` you need to install
polkit; otherwise you need to add yourself in the `seat` group and
enable/start the seatd daemon.

When dwl is run with no arguments, it will launch the server and begin handling
any shortcuts configured in `config.h`. There is no status bar or other
decoration initially; these are instead clients that can be run within
the Wayland session.
Do note that the background color is black.

If you would like to run a script or command automatically at startup, you can
specify the command using the `-s` option. This command will be executed as a
shell command using `/bin/sh -c`.  It serves a similar function to `.xinitrc`,
but differs in that the display server will not shut down when this process
terminates. Instead, dwl will send this process a SIGTERM at shutdown and wait
for it to terminate (if it hasn't already). This makes it ideal for execing into
a user service manager like [s6], [anopa], [runit], [dinit], or [`systemd --user`].

Note: The `-s` command is run as a *child process* of dwl, which means that it
does not have the ability to affect the environment of dwl or of any processes
that it spawns. If you need to set environment variables that affect the entire
dwl session, these must be set prior to running dwl. For example, Wayland
requires a valid `XDG_RUNTIME_DIR`, which is usually set up by a session manager
such as `elogind` or `systemd-logind`.  If your system doesn't do this
automatically, you will need to configure it prior to launching `dwl`, e.g.:

    export XDG_RUNTIME_DIR=/tmp/xdg-runtime-$(id -u)
    mkdir -p $XDG_RUNTIME_DIR
    dwl

### Status information

Information about selected layouts, current window title, app-id, and
selected/occupied/urgent tags is written to the stdin of the `-s` command (see
the `printstatus()` function for details).  This information can be used to
populate an external status bar with a script that parses the information.
Failing to read this information will cause dwl to block, so if you do want to
run a startup command that does not consume the status information, you can
close standard input with the `<&-` shell redirection, for example:

    dwl -s 'foot --server <&-'

If your startup command is a shell script, you can achieve the same inside the
script with the line

    exec <&-

To get a list of status bars that work with dwl consult our [wiki].

## Replacements for X applications

You can find a [list of useful resources on our wiki].

## Acknowledgements

dwl began by extending the TinyWL example provided (CC0) by the sway/wlroots
developers. This was made possible in many cases by looking at how sway
accomplished something, then trying to do the same in as suckless a way as
possible.

Many thanks to suckless.org and the dwm developers and community for the
inspiration, and to the various contributors to the project, including:

- **Devin J. Pohly for creating and nurturing the fledgling project**
- Alexander Courtis for the XWayland implementation
- Guido Cella for the layer-shell protocol implementation, patch maintenance,
  and for helping to keep the project running
- Stivvo for output management and fullscreen support, and patch maintenance


[Discord server]: https://discord.gg/jJxZnrGPWN
[#dwl on Libera Chat]: https://web.libera.chat/?channels=#dwl
[Wayland]: https://wayland.freedesktop.org/
[wlroots]: https://gitlab.freedesktop.org/wlroots/wlroots/
[wlroots-next branch]: https://codeberg.org/dwl/dwl/src/branch/wlroots-next
[patches repository]: https://codeberg.org/dwl/dwl-patches
[patches wiki]: https://codeberg.org/dwl/dwl-patches/wiki
[s6]: https://skarnet.org/software/s6/
[anopa]: https://jjacky.com/anopa/
[runit]: http://smarden.org/runit/faq.html#userservices
[dinit]: https://davmac.org/projects/dinit/
[`systemd --user`]: https://wiki.archlinux.org/title/Systemd/User
[wiki]: https://codeberg.org/dwl/dwl/wiki/Home#compatible-status-bars
[list of useful resources on our wiki]:
    https://codeberg.org/dwl/dwl/wiki/Home#migrating-from-x
