# Heist Game Project

> A third-person heist game built in Unreal Engine 5, featuring a sophisticated AI guard system using custom written C++ tasks, behaviour trees and Environmental Query System (EQS).

![Unreal Engine 5](https://img.shields.io/badge/Unreal%20Engine-5-black?style=flat&logo=unrealengine)
![C++](https://img.shields.io/badge/C++-blue?style=flat&logo=cplusplus)
![Blueprint](https://img.shields.io/badge/Blueprint-grey?style=flat)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=flat&logo=windows)

---

## About the Project

Heist Game is a third-person stealth game where the player must navigate guard-patrolled environments to extract a target jewel.
 
The core focus of development was to build a sophisticated and reactive AI system that creates immersion through patrolling guards, reactive alarm responses, and a convincing fleeing system.
 
This was a solo second-year project developed in Unreal Engine 5 to deepen my understanding of AI architecture and gameplay systems within the engine.

---

## Features

- **AI Behaviour Trees** — Guards operate on two dynamically switching behaviour trees, transitioning from patrol to aggressive depending on player visibility
- **Environmental Query System (EQS)** — Guards use EQS to dynamically flee from the player when reaching a low health threshold at runtime
- **Third-person character controller** — Custom movement with jumping and crouching, alongside an animation blueprint using blend spaces
- **Stealth mechanics** — Line-of-sight checks performed by custom C++ tasks determine a guard's current state

---

## AI Systems Overview

The guard AI is built using UE5's native AI framework:
 
- **AIController** — Custom C++ controller class managing behaviour tree transitions and guard location upon possession
- **Behaviour Trees** — Split into two types: *Passive* and *Aggressive*. Handles all guard logic including patrolling and chasing the player, with the tree switching dynamically based on player visibility
- **EQS Queries** — Runtime spatial queries handle guard fleeing when health is low, achieved through a combination of EQS scoring and filtering


---

## Future Ideas

- Advanced AI guards — AI Perception system, guard investigation and communication, in-depth EQS queries
- Objective variation — safe cracking, document theft, hostage scenarios
- Smoother player movement — vaulting and crawling

--- 

## Built With
 
- [Unreal Engine 5](https://www.unrealengine.com/)
- C++ and Blueprints
- UE5 AI framework — Behaviour Trees, Blackboard, EQS
- Target platform: PC (Windows 64-bit)

---

### Installation
 
1. Clone the repository
   ```bash
   git clone https://github.com/JAGreen06/Heist-Game-Project
   ```
   
2. Right-click `HeistGame.uproject` and select **Generate Visual Studio project files**
4. Open `HeistGame.uproject` in Unreal Engine 5
5. Press **Play**
