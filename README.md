ExtraNotes
==========

ExtraNotes is a simple plugin for keeping text or image notes alongside an
arrangement. Formerly called "AUNotes", ExtraNotes now supports Mac OSX,
Windows, and Linux with 64-bit versions on all platforms (whereas AUNotes was
an AudioUnit plugin for Mac OSX only).

![ExtraNotes Text Editing](http://static.teragonaudio.com/ta_extranotes.png)
![ExtraNotes Image Editing](http://static.teragonaudio.com/ta_extranotes_image.png)


Usage
-----

To use, simply insert the plugin in the desired channel in your arrangement,
and type away. Your changes will be saved automatically when you save your
document in the host sequencer. You can have several instances of ExtraNotes
in an arrangement, each with their own contents. Since ExtraNotes can only
hold a single image, you'll need multiple instances of the plugin if you want
to save several images.

ExtraNotes can hold an unlimited amount of text and a single image. The "Text"
and "Image" buttons on the top will toggle the editor to switch between
editing the text note or the image.

You can import content into the plug-in using the "Import" button on the upper
right-hand corner. The file browser will filter the available files you can
choose based on the active tab. So to import an image, the "Image" button must
first be selected.

Pressing "Clear" will remove contents of the current editor tab. The contents
of the other unselected tab will not be affected.


Limitations
-----------

Unfortunately, text input in plugins is still problematic for many sequencers.
When starting a new instance of ExtraNotes, the default text may contain
details about an unsupported sequencer or operating system.

I have tried to test the plug-in on as many sequencers as possible, however if
you discover one which does not work, please email support (at) teragonaudio
(dot) com with your system information. Likewise, if ExtraNotes warns you
about a possibly broken host which works fine, please email the support
address so that I can add the host to the whitelist of known working
sequencers.

It is possible to use cut/copy/paste within the text editor, however many
sequencers intercept these keystrokes for themselves. In this case, you can
access these functions by right-clicking in the note to bring up a context
menu.

ExtraNotes only supports plain-text notes (ie, no bold, italics, or other rich
text). Only JPG/PNG/GIF (non-animated) images are supported. It is not
possible to export content from ExtraNotes to regular files.


License
-------

ExtraNotes is licensed under the GPL2. Please see the LICENSE.txt file
distributed with the software for more details.

