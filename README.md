<br />

<div align="center">


<img src="assets/logo.jpg" alt="logo" width="200" div al ign=center />

</div>

  <h1 align="center">Facial Decoration</h1>

  <p align="center">
    Help you to discover a brand new self!
    <br />
      <a href="https://github.com/RTEP-zero-to-one/FacialDecoration/wiki"><strong>Full the docs »</strong></a>
    <br />
    <br />
    <a href="https://twitter.com/FacialDecorati1">Twitter</a> 
    ·
    <a href="https://www.facebook.com/profile.php?id=100075055657851">Facebook</a>
    ·
    <a href="#">YouTube</a>
  </p>






</p>

![Contributors](https://img.shields.io/github/contributors/RTEP-zero-to-one/FacialDecorationTracing?style=for-the-badge)
![GitHub Repo stars](https://img.shields.io/github/stars/RTEP-zero-to-one/FacialDecorationTracing?style=for-the-badge)
![Issues](https://img.shields.io/github/issues-raw/RTEP-zero-to-one/FacialDecorationTracing?style=for-the-badge)
![Apache-2.0 License](https://img.shields.io/badge/LICENSE-Apache--2.0-yellowgreen?style=for-the-badge)



<details open="open">
  <summary>Catalogue</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#components-used">Components Used</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>




## About The Project

The facial decoration is a real-time face detection and instant beautification application based on Raspberry Pi.
In order to perform simple beauty functions, it can automatically and accurately identify the user's facial features. Then they can use whitening and dermabrasion functions to get flawless skin and put cute stickers on their face. Besides, this application has a series of filters, which could be selected when taking selfies or live streaming.

### Components Used

* OpenCV C++ API
* QT C++ API
* C++ Timer
### Built With

* GitHub Wiki
* Typora



## Getting Started


### Prerequisites

OpenCV and Qt5 are required. Users can use following script to install:

  ```sh
  sh install_dependency.sh
  ```

### Stand-alone Application

If you want to quickly download and run our project, simply use the script we provide:.
```
bash <(curl -s -S -L https://raw.githubusercontent.com/RTEP-zero-to-one/FacialDecoration/main/run_application.sh)
```

This installation is currently only available for **Linux** machines. We have tested our software on

- Ubuntu 20.04 LTS with x86_64
- Raspberry Pi 4B with Raspberry Pi OS

### Build Application Manually
1. Clone this repository
```
git clone https://github.com/RTEP-zero-to-one/FacialDecoration.git
```
2. Install Dependency with Script (Installation of Qt and OpenCV may consume a lot of time)
```
cd FacialDecoration && sh install_dependency.sh
```
3. Build the Application
```
sh build.sh
```
4. Run the Application
```
./FacialDecoration
```

### Run Test
1. Finish step 1~3 in Build Application
2. Change **UnitTest** file path to $ProjectRootDir, because the resource files are not compiled with CMake and they are not in build directory.
```
cp build/UnitTest .
```
3. Run UnitTest
```
./UnitTest
```



## Usage

* Include screenshots, video demos and code examples to demonstrate the project



## Roadmap

See the [open issues](https://github.com/RTEP-zero-to-one/FacialDecorationTracing/issues) for a list of proposed features (and known issues).



## License

Distributed under the Apache License 2.0. See [`LICENSE`](https://github.com/RTEP-zero-to-one/FacialDecorationTracing/blob/dev/LICENSE) for more information.



## Contact

This project is being completed by a team of Msc Computer System Engineering students at the University of Glasgow:

* [Tianze Zhang](https://github.com/ZTZWILL) 
* [Xunan Wang](https://github.com/SheenaWang11)
* [Luoxuan Peng](https://github.com/Xxxuan11)
* [Heting Ying](https://github.com/XeonHis)




## Acknowledgements
* 
* 
* 
