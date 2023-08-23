**What is OpenGL?**
- OpenGL is a graphics API (application programming interface) which allows us to access graphics card.
- It's a specification.
- OpenGL is written by the GPU manufacturer.
- It is cross-platform, easiest way to ship a game on multiple platforms

**Modern vs Legacy**
Legacy OpenGL
- It was a set of presets.
- easy to use, code is short.
- less control.
Modern OpenGL
- provides more control.
- the biggest difference between the two is shaders.

**What are shaders?**
- It's a program, a code that runs on GPU.
When we write code in C++ or Java it runs on the CPU but we are dealing with graphics so we have to move code from CPU to GPU because it will run faster on the GPU.
- Shaders allow us to write code on the GPU


# Setup
create a window to draw all graphics. Multi-platform support should work on all three platforms: Linux, macOS, and windows. 

Win32 API to make a window on windows.

**Library GLFW**
- This library will provide the appropriate platform layer so we can run it on all platforms.
- create a window >> create an OpenGL context >> give us access to things like input

**To download GLFW -**
[http://www.glfw.org/](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbHJDQnNvMWx1LThBcG5LbE9VMjZCQzBtSE5rZ3xBQ3Jtc0trZkViN3diSnBvcVhpWk5BMGZ2ME1jNGVCZ3lsWkY2bXl3MHRDSXlTZndjM1hKVWdqLTREd0d6QzZCbC05akJDSnBHYU9UM3hDRks1QVJsZWhlT05VOVZEM19YdEVBekY4c1NYaDhQQWtMcVQ4SHVuNA&q=http%3A%2F%2Fwww.glfw.org%2F&v=OR4fNpBjmq8)

**Setup for Mac**
Homebrew : [http://brew.sh/](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbDNpUlVQTkFoanlQUmZDVk1yTFZkTXczOFZTUXxBQ3Jtc0tsRU1paEo1RWczdkZ3QWJ2dC1wMTdGenctTGR1WDU3RjZBYi1TWDk2VFpwMnpZaEIwUnJFWmo0Q3pjTzNMRlAxNnZ3UjVwSGVXWkdrRHdpQlN2dkd1UzNCOVpCNHc4UEJMUzI1RUFfRGJaMEUxMFZkcw&q=http%3A%2F%2Fbrew.sh%2F&v=Tz0dq2krCW8)
GLEW Download Link: [http://glew.sourceforge.net/index.html](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqa1RHOU1xekRnLVNwaTh3UlYxMkdJbGtRV3pyZ3xBQ3Jtc0tuTWpVN0dObjg2eVlBaWZQS1JzS1E1dXg5Z1E1eGxCOXdUNTBUektxTG1pd0lwdDh3UDJVQnA0RlpOcGk0aGNNd05EaU5qejFvTXpDUmxJUERqVnlNd29OTFZTS3pfWW91LV9oWHpsVUhFUXpVR0J5UQ&q=http%3A%2F%2Fglew.sourceforge.net%2Findex.html&v=Tz0dq2krCW8) 
GLFW Download Link: [http://www.glfw.org/](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbkN4RkxUdHJLTi1kX2Fqb3BMa3VpSGc2QkVkQXxBQ3Jtc0trSUhvdVFHUnBwdFFCY1lwb0xFOXRCTXNTcWVkSEdiMTUzeW1jZlQxU3JrUEtqZER6blFia1ZpLVFZSmJHTk1IanVJdUs2dzRzM19hNFBHSGZXc09WWXBVN0ZjZFNwZm5WRWlkS1g1d1NtRm01VmJkYw&q=http%3A%2F%2Fwww.glfw.org%2F&v=Tz0dq2krCW8) 
Source Code: [https://github.com/SonarSystems/Moder...](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqblRZSGFOa3J6d0NaS1RvbXI4VzV3WjFTYnBJUXxBQ3Jtc0tsSE9kVGN5UTExWGdwekJLNE5Yb3R3SVRlTFVUWEtxQ09Dbm9YZ0NUMzNFczhDZi1lVDVWX3ZFbFdxLU9IZUJLWTg2dEdwYnhueUhneU5sUTFMTnlGM095NEFvWnd1WUVnT2ZwbkM0SXNJNmJaZUU3cw&q=https%3A%2F%2Fgithub.com%2FSonarSystems%2FModern-OpenGL-Tutorials&v=Tz0dq2krCW8)












