_Use Case Name_        AbortFileTransfer

_Participating Actors_ Initiated by Basic User

1. Basic User clicks the cancel button in the interface
> 2. Interface responds with a message asking the user if they are sure
3. If user clicks yes, the client software deletes the partially downloaded file
4. The client software then removes the download from the list of downloads

_Entry Condition_
  * The Basic User is downloading a file or files.

_Exit Condition_
  * The GUI successfully deletes the partially downloaded files and removes the downloads from the list of active downloads. OR
  * The Basic User clicks "no" in the confirmation dialogue box, thereby cancelling the cancellation.
_Quality Requirements_
  * The dialogue box only appears for 10 seconds, before the cancellation is automatically cancelled.

**Activity Diagram**

![http://nmt-cs326-g5.googlecode.com/files/act_aborttransfer.jpeg](http://nmt-cs326-g5.googlecode.com/files/act_aborttransfer.jpeg)