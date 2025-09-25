# My Gimp (SFML)

> A lightweight, extensible image editor built with **C++**, **SFML**, and **CMake**. Designed for learning graphics programming and prototyping simple GIMP‑like workflows.

---

## ✨ Features

* **Canvas & Layers**: Multi‑layer bitmap editing with per‑layer visibility and opacity.
* **Drawing Tools**: Pencil, brush, eraser, line, rectangle/ellipse (filled & outline).
* **Selections**: Rectangular marquee with copy/cut/paste.
* **Filters**: Grayscale, invert colors, brightness/contrast, blur (box/gaussian*), sharpen*.
* **History**: Undo/redo stack with memory‑aware checkpoints.
* **IO**: Load/Save PNG, JPG, BMP (via SFML image codecs). Export to PNG.
* **Shortcuts**: Familiar hotkeys (Ctrl+N/O/S/Z/Y, etc.).
* **Theming**: Light/Dark UI theme toggle.
* **Plugin Hooks**: Minimal plugin API (C++) for custom filters/tools.*

> *Starred items are optional/behind feature flags depending on your current milestone.

---

## 🧰 Tech Stack

* **Language**: C++17 (or later)
* **Graphics**: [SFML 2.6+](https://www.sfml-dev.org/)
* **Build System**: CMake ≥ 3.20
* **CI**: GitHub Actions (Linux/Windows/macOS) – build & tests
* **Code Style**: google format

---

## 📦 Project Structure

```
MyGimp/
├─ CMakeLists.txt
├─ cmake/                      # CMake helpers (FetchContent, warnings, etc.)
├─ external/                   # Pinned third‑party libs (optional)
├─ src/
│  ├─ app/                     # main(), window loop, menus, dispatch
│  ├─ core/                    # image, layer, selection, history, commands
│  ├─ tools/                   # brush, eraser, shapes… (ITool hierarchy)
│  ├─ filters/                 # grayscale, blur, sharpen… (IFilter)
│  ├─ ui/                      # widgets, panels, color picker, dock layout
│  └─ platform/                # filesystem, dialogs, clipboard
├─ include/                    # public headers (if lib split)
├─ assets/                     # fonts, icons, demo images
├─ tests/                      # unit/functional tests
├─ docs/
│  └─ screenshots/             # README images
```

---

## 🚀 Getting Started

### Prerequisites

* **C++ compiler** with C++17 support
* **CMake ≥ 3.20**
* **SFML 2.6+** (fetched automatically via CMake `FetchContent` or system packages)
* **Git**

### Clone

```bash
git clone https://github.com/<you>/my-gimp.git
cd my-gimp
```

### Configure & Build (CMake)

```bash
# Configure (Debug by default)
cmake -S . -B build -DMYGIMP_ENABLE_TESTS=ON -DMYGIMP_FETCH_SFML=ON

# Build
cmake --build build --config Debug -j

# Run
./build/MyGimp
```

### Run Tests

```bash
ctest --test-dir build --output-on-failure
```

> If you prefer system packages, set `-DMYGIMP_FETCH_SFML=OFF` and make sure SFML is discoverable (e.g., `find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)`).
