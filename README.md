# ytd : A daemon for backgroud playback of yt-dlp
`ytd` is a server that can be used to play the audio of videos hosted on services supported by [`yt-dlp`](https://github.com/yt-dlp/yt-dlp).

## Dependencies
- Qt Core
- Qt Multimedia
- Qt WebSocket
- [`yt-dlp`](https://github.com/yt-dlp/yt-dlp)
- `qmake` (build time)

## How to build
First create a build directory :
```bash
mkdir build
cd build
```

Then generate the `Makefile` :
```bash
qmake -makefile ../ytd.pro
```

And finally compile :
```bash
make -j$(nproc)
```

## Exemple client
- [ytd-cli-client](https://github.com/ttcchhmm/ytd-cli-client) : a minimal command line client for `ytd`

## Protocol
`ytd` uses a WebSocket to communicate with its clients. To learn more about it, please read the [documentation](docs/Protocol.md).