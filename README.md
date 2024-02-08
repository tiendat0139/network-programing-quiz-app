<!-- PROJECT LOGO -->
<br />
<div align="center">

  <h3 align="center">Online Exam Project</h3>

  <p align="center">
    Project online multiple choice exam system
  </p>
</div>

<!-- ABOUT THE PROJECT -->
## About The Project
Online multiple choice exam system with functions to create exam room, create exam questions, join exam room, start exam room, end exam room, practice mode, admin, real-time mechanism


### Built With

This section should list any major frameworks/libraries used to bootstrap your project. Leave any add-ons/plugins for the acknowledgements section. Here are a few examples.

* Qt
* TCP C++

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* Install Qt5
  ```sh
  sudo apt-get install qt5-default
  ```
* Install library for Qt chart
  ```sh
  sudo apt install libqt5charts5-dev
  ```

### Installation
1. Clone the repo
   ```sh
   git@github.com:tiendat0139/network-programing-quiz-app.git
   ```
2. Run server
   ```sh
   cd src/app/server
   make all
   ./server 5000
   ```
3. Config command line arguments in Qt
   ```sh
   127.0.0.1 5000
   ```
   
4. Run Qt

