# MultiLingual Assistive Device (MAD)

> **A C++ translation device integrating Google Cloud AI APIs** — supporting text, speech, and voice output across dozens of languages. Designed for portable use on a **Raspberry Pi** with an LCD display, with a full terminal-based demo for development and testing.

---

## Features

| Mode | Description |
|------|-------------|
| **Text-to-Text** | Type text in one language, get a translation in another via Google Translate API |
| **Speech-to-Text** | Record audio via microphone → transcribe via Google Speech-to-Text → translate output |
| **Text-to-Speech** | Type text → translate → hear the result spoken aloud via Google Text-to-Speech |

- **80+ language codes** supported (ISO 639-1) with Google Voice format conversion
- **History logging** to `HistoryLog.txt` for all translations
- **Dual interface:** Terminal demo (cross-platform) + Raspberry Pi LCD display (via WiringPi)
- **Audio pipeline:** Record → Base64 encode → API → decode → validate WAV → play

---

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                      Terminal / LCD UI                       │
├──────────┬──────────┬──────────────────────────────────────┤
│ TtT Mode │ StT Mode │              TtS Mode                 │
│ (Text→   │ (Speech→ │              (Text→Text→              │
│  Text)   │  Text)   │               Speech)                 │
├──────────┴──────────┴──────────────────────────────────────┤
│                   Translation Engine                         │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────────┐   │
│  │ Google Cloud │  │ Google Cloud │  │ Google Cloud     │   │
│  │ Translate    │  │ Speech-to-   │  │ Text-to-Speech   │   │
│  │ API          │  │ Text API     │  │ API              │   │
│  └──────────────┘  └──────────────┘  └──────────────────┘   │
├─────────────────────────────────────────────────────────────┤
│                    Audio Pipeline                            │
│  Record (PortAudio) → Encode (Base64) → API → Decode → Play │
└─────────────────────────────────────────────────────────────┘
```

---

## Tech Stack

| Layer | Technology |
|-------|-----------|
| **Language** | C++17 |
| **Cloud APIs** | Google Cloud Translation, Text-to-Speech, Speech-to-Text |
| **HTTP Client** | libcurl |
| **JSON Parsing** | jsoncpp |
| **Audio Capture** | PortAudio |
| **Audio Playback** | SDL2 |
| **GPIO / LCD** | WiringPi (Raspberry Pi) |
| **Build System** | GNU Make |
| **Audio Format** | WAV (PCM LINEAR16) |

---

## Quick Start

### Prerequisites

```bash
sudo apt-get install libcurl4-openssl-dev libjsoncpp-dev portaudio19-dev libsdl2-dev
```

### Setup API Keys

This project requires **3 Google Cloud API keys**. Get them from the [Google Cloud Console](https://console.cloud.google.com/apis/credentials):

```bash
export GOOGLE_TRANSLATE_API_KEY="your_key_here"
export GOOGLE_STT_API_KEY="your_key_here"
export GOOGLE_TTS_API_KEY="your_key_here"
```

### Build & Run (Terminal Mode)

```bash
make
./program.exe
```

### Run on Raspberry Pi with LCD

Uncomment the LCD code in `src/displayMain.cpp` and install WiringPi:

```bash
sudo apt-get install wiringpi
```

---

## Project Structure

```
├── src/
│   ├── main.cpp                 # Entry point
│   ├── terminalDemo.cpp/.h      # Terminal-based UI (3 translation modes)
│   ├── displayMain.cpp/.h       # Raspberry Pi LCD display logic
│   ├── textTranslation.cpp/.h   # Google Translate API client
│   ├── textToSpeech.cpp/.h      # Google Text-to-Speech API client
│   ├── speechToText.cpp/.h      # Google Speech-to-Text API client
│   ├── audioRecorder.cpp/.h     # Microphone recording via PortAudio
│   ├── wavPlayer.cpp/.h         # WAV audio playback via SDL2
│   ├── fileEncoder.cpp/.h       # Base64 encode/decode utilities
│   └── languageCodes.cpp/.h     # ISO 639-1 language code validation
├── Makefile
├── Settings.txt                 # Default language/method config
└── vcpkg.json                   # vcpkg dependency manifest
```

---

## License

This project was developed as part of **CS3307 — Software Design & Specification** at **Western University**.

---

## Authors

- **Mert Osoydan**
- Noah Kellett
- Fuad Ghareeb
