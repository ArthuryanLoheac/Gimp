# My Gimp (C++/SFML) – Minimal Starter

> Setting up a clean project structure and an extensible CMake for starting the My Gimp project.

---

## 📁 Minimal Directory Structure

```
MyGimp/
├─ CMakeLists.txt
├─ cmake/               # additional CMake scripts (optional)
├─ include/             # headers (.hpp)
├─ src/                 # sources (.cpp)
├─ tests/               # unit tests (optional)
└─ extern/              # third-party dependencies (empty initially)
```

---

## 🛠️ Prerequisites

- **C++ compiler** supporting C++20 or higher
- **CMake ≥ 3.20**
- **SFML 2.6+** (installed on your system or via package manager)
- **Git**

---

## ⚡ Installation & Build

### 1. Clone the project

```bash
git clone https://github.com/<you>/my-gimp.git
cd my-gimp
```

### 2. Configure the project (Debug by default)

```bash
cmake -S . -B build
```

> For Release: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release`

### 3. Build

```bash
cmake --build build
```

### 4. Run the executable

```bash
./build/bin/my_gimp
```

---

## 🔗 SFML Integration

- SFML is detected via `find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)`.
- If SFML is not installed, follow the official documentation: [SFML Install](https://www.sfml-dev.org/tutorials/2.6/)

---

## 🧪 Preparing for Tests

- A `tests/` folder is provided for future unit tests (optional at this stage).

---

## 📝 Notes

- The structure and CMake are designed to be easily extensible (adding modules, options, tests, etc.).
- This base will serve as the foundation for all future features.

