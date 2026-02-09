# MagisV2-Add-On

This repository provides example code and prebuilt firmware (.hex) files for external modules (Add-Ons) compatible with the MagisV2 drone firmware.  
Add-Ons include sensor modules, motor modules, and other peripheral extensions that enhance MagisV2-powered drones.

---

## Add-On Project Codes

Each add-on has a unique 8-character project identifier with prefix **X2-**.

| Add-On Name | Project Code |
|-------------|--------------|
| MiniClaw 2.0 | X2_MCLAW |
| LaserTag | X2_LASRT |
| GasSense-2 | X2_GS002 |
| GasSense-135 | X2_GS135 |
| GasSense-06 | X2_GS006 |
| FlameSense | X2_FLMSN |
| IRShield | X2_IRSHD |
| SkyBanner | X2_SKYBN |
| AudioSense | X2_AUDSN |
| LightSense | X2_LGTSN |
| X-Ranging | X2_XRANG |
| X-Hybrid | X2_XHYBD |
| GlowLite | X2_GLITE |
| Hooter | X2_HOOTR |
| PlutoGlow | X2_PGLOW |

---

## Repository Structure

The repository is organized by individual add-ons.

Each **Add-On folder** contains two main subdirectories:

```
AddOnName/
├── PlutoBlocks/
└── PlutoIde/
```

### 1. PlutoBlocks Folder

This folder contains resources required for Blockly-based programming using PlutoBlocks.

**Files inside PlutoBlocks:**

```
PlutoBlocks/
├── addonname.json
├── addonname.pdf
└── PlutoBlocksRef.png
```

| File | Description |
|------|-------------|
| addonname.json | Blockly configuration file for the add-on |
| addonname.pdf | Documentation for the add-on usage in PlutoBlocks |
| PlutoBlocksRef.png | Reference image for block implementation |

---

### 2. PlutoIde Folder

This folder contains project files for PlutoIDE based development using VS Code.

**Files inside PlutoIde:**

```
PlutoIde/
├── PlutoPilot.cpp
└── plutoide.ini
```

| File | Description |
|------|-------------|
| PlutoPilot.cpp | Main source code file implementing the add-on functionality for PlutoIDE |
| plutoide.ini | Project configuration file containing PlutoIDE project details |

---

## Usage

- Choose the add-on folder you want to work with.
- Use the **PlutoBlocks** folder if you are working with Blockly-based programming.
- Use the **PlutoIde** folder if you are developing using PlutoIDE on VS Code.


---

## Compatibility

All add-ons in this repository are designed to work with:

- **MagisV2 Firmware**
- PlutoIDE Development Environment
- PlutoBlocks Visual Programming Interface

---

Happy Building with MagisV2 Add-Ons! 🚀
