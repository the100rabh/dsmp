# Damn Small Media Player (DSMP) #

I know there are loads of mp3 players available, so why one more. The motivation behind me writing this app is that I am fed up with the ever increasing size of mp3 players. This is meant to ease my pain :-P. I aim to keep its size below 2MB at all costs. May at the cost of feature, buts its fine

**This is current in Beta stage. Please file your bugs at http://code.google.com/p/dsmp/issues/list.**

**Currently only supports windows XP, Vista  and Win7 not supported**
## About the Player ##

Using the player:
  * New icons added **NEW**
  * Minor bugs related to selection fixed **NEW**
  * Ctrl+A on the List Ctrl selects all the files in the list of files **NEW**
  * Global HotKeys added for Previous(Ctrl+Alt+Z), Play/Pause(Ctrl+Alt+X), Stop(Ctrl+Alt+C) and Next(Ctrl+Alt+V) **NEW**
  * Download the exe and run it. Its that simple.
  * Click on Add button and select the files/folders you want to add to the playlist
  * Play, stop, previous and next button work as expected.
  * Shortcut keys (Z= Previous, X= Play/Pause, C = Pause, V= Next)
  * Playlist Queue(Select the file and click on Insert key to add file to queue)
  * Saving file list, click on Playlist button and select save. To load use the load option.

## About the Code ##

The app is written using [wxWidgets](http://wxwidgets.org) library in C++. I used the [wxDev-Cpp IDE](http://wxdsgn.sourceforge.net/) for development.

Though I have written it in windows, it can be compiled in other platforms like Mac or Linux also without any code change :-). This is thanks to wxWidgets Library which is cross-platform. You need to write a different make file for those platforms. In case you do, please let me know so that I can make it available for download for others too.

To reduce size further I have used [UPX](http://upx.sourceforge.net/) which is pretty cool and is also available for Linux too.

You can contact me at dsmp.saurabh _a!_ GM@ail.com for further info.


**Note :** In addition to GPL, if you are hosting the exe from your site, you cannot charge for downloads in any manner.

More about it at my blog http://the100rabh.blogspot.com/2009/04/damn-small-media-player-my-tiny-mp3.html