---
layout: post
title: OpenGL-3D-GameEngine
tags: OpenGL,C++,Graphics API
description: To create a 3D Game Engine using OpenGL librarires in C++ and make a game like checkers/chess.
---

--[Anish Mahadevan](https://github.com/Faulty404)
--[Ritika Nankar](https://github.com/Ritika128)
# Overview of the Project 

## What is OpenGL?

OpenGL is a **graphics API**. API stands for *application program interface*. It allows us to access our GPU (Graphics Processing Unit) and perform functions using it.

OpenGL is one of the many graphics APIs available in the market. Examples of a few others are:
- Direct3D
- Vulcan
- Metal

At its core, OpenGL is a specification that basically lists that so and so function should take so and so parameters and perform so and so task.

An advantage of OpenGL over other graphics APIs is that it is a cross-platform API. In most devices, the OpenGL 

### Modern vs Legacy OpenGL

Legacy OpenGL

- It was a set of presets.
- Easy to use, code is short.
- Provides less control.

Modern OpenGL

- Provides more control.
- The biggest difference between the two is the implementation of shaders.

### What are Shaders?

- It's a program, a code that runs on the GPU (Graphics Processing Unit).

When we write code in C++ or Java it runs on the CPU but we are dealing with graphics so we have to move code from CPU to GPU because it will run faster on the GPU.

- Shaders allow us to write code on the GPU.

## What is a Game Engine?

A game engine is a software framework primarily designed for the development of video games and generally includes relevant libraries.

The purpose of a game engine is to provide a suite of visual development tools in addition to reusable software components to build/make a game.

Detailed information about a game engine is given in the [wikipedia page](https://en.wikipedia.org/wiki/Game_engine).

## C++

The code to make the game engine using OpenGL libraries will be written in C++ which is a high level programming language. 

C++ is one of the most popular programming languages and is used in most of today's operating systems, GUIs and embedded systems.

## Overview of the project

Through this project , we aim to develop a game engine and make a game similar to Chess/Checkers.

To do this we must learn the fundamentals of OpenGL libraries and how the API uses Vertex Buffers , Shaders and other pre-built libraries to render and display graphics on the display. 

The implementation of the code will be done using C++.




