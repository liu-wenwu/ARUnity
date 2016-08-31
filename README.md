# Readme for ARUnity

## About
ARUnity is a framework using unity to achieve augmented reality based on [OpenCV][1].
I have completed the augmented reality for marker on the windows platform.
The next plan is to complete the natural feature tracking.

## Usage

 1. Download : `git clone https://github.com/liu-wenwu/ARUnity.git`
 2. Open project "Plugins/win32/arunity.sln" with Visual Studio 2013.
 3. Configure Sub project `arunity`with x86 & release mode, compile & generate `arunity.dll`,then copy this file to the folder `Unity/ARUnity/Assets/Plugins/x86`.
 4. Sub project `test` is used to test the algorithm and interface.
 5. Open `Unity 5.4.0f3 (32-bit)`,click `OPEN`，select the folder `Unity/ARUnity`.
 6. Open the scene `test.unity`,we will see Unity Editor 
 7. Make sure your computer is connected to a camera.Push the play button,put the marker in the camera scene,then we will find a cube standing on the marker.
 
![image](https://github.com/liu-wenwu/ARUnity/raw/master/Doc/editor_demo.png)
 ![image](https://github.com/liu-wenwu/ARUnity/raw/master/Doc/running_demo.png)

## Thanks
[ARToolkit][2]
[aipiano][3]


  [1]: https://github.com/opencv/opencv
  [2]: https://github.com/liu-wenwu/artoolkit5 "ARToolkit"
  [3]: http://aipiano.farbox.com/ "aipiano"