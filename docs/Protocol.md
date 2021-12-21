# The ytd server protocol
`ytd` communicates with its clients through a WebSocket and supports sending and receving data.

## Updating the client status
### Player state and metadata
`ytd` will send the following data to its clients through text formatted as JSON :
- Playing/paused/stoppped state (`state`: string)
- Player queue (`queue`: array)
  - Name of media (`name`: string)
  - Length in seconds (`duration`: integer)
  - Location (`location`: string)
  - Track ID (`trackID`: string)
- Index of the currently playing media (`current`: integer)
- The current volume in the [0; 100] range (`volume`: integer)

This data is sent each time any of these is attributes are changed.

### Position in the currently playing media
To avoid sending too much data, the position of the currently playing media is sent separately from the rest of the data. The position is sent through text with the `pos` header, followed by the number of milliseconds. Exemple : `pos 298750`.

## Sending requests to the server
The client can send requests to the server through the WebSocket as well. The following commands are supported through the text based channel :

### Adding content to the queue
Command : `add`

Arguments : `url`

Exemple : `add https://www.youtube.com/watch?v=dQw4w9WgXcQ`

Supports both individual videos and playlists.

### Resuming playback
Command : `play`

Arguments : *none*

Resumes playback or start it from the beginning of the queue if the player is stopped. Does nothing if already playing.

### Pausing playback
Command : `pause`

Arguments : *none*

Pauses playback. Does nothing if already paused or stopped.

### Stopping playback
Command : `stop`

Arguments : *none*

Pauses playback and sets the currently playing media to the first one in the queue.

### Loading the next media
Command : `next`

Arguments : *none*

Skips to the next media.

### Load a media from the queue
Command : `load`

Arguments : `trackNumber`

Exemple : `load 1`

Load the media at the specified position in the queue. Does not resume playback right after !

### Resetting the player
Command : `reset`

Arguments : *none*

Empties the queue and stops the player.

### Removing an element from the queue
Command : `remove`

Arguments : `trackNumber`

Exemple : `remove 2`

Removes a media from the queue.

### Set the player position
Command : `position`

Arguments : `newPosition`

Exemple : `position 0`

Sets the position of the player in the currently playing media. Works with milliseconds.

### Set the volume
Command : `volume`

Arguments : `newVolume`

Exemple : `volume 50`

Sets a new volume.

**Warning :** This is using a linear scale, and not a logarithmic scale ! See the [Qt documentation for more](https://doc.qt.io/qt-5/qmediaplayer.html#volume-prop).