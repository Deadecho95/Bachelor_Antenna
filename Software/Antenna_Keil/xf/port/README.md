# XF Ports

## Introduction
An XF (execution framework) consist of a view classes which some need to be adjusted
when used on an other platform. 

Following you will find a list of classes which may be adjusted/reimplemented when
changing to an other platform/environment:
 - XF
 - ResourceFactory
 - TimeoutManager
 - Dispatcher
 - EventQueue
 - Thread
 - Mutex

These classes are also named `port classes` because they can be ported to an other
platform. All port classes can be found in the _port_ folder whereas every port is
located in a separate folder.

In case you are going to implement an OS-less XF (hence an IDF) usually you do not
need to implement the classes Thread and Mutex

## Default Port Classes
There are already some default port class implementations present. They are 
located in the `default` folder and may suit your needs for a first version
of your XF.

## Port Folder Structure
In case you want to add support for an other platform to the XF, you need to add a 
subfolder to the _port_ folder and put the port class files in there. Best is to
take an already present port which is most similar to what you need, rename it and
start adaption of these files. 

You may also mix-up you port with classes from the _default_ folder and your custom
folder (or even reference classes from other ports).

## Available Ports

Here is a list of currently available ports:

| Port Name | OS | Platform | Folder Name | Description |
|--|--|--|--|--|
| PORT_IDF_QT | Qt (IDF) | Qt library based implementation | idf-qt | XF support for OS X, Linux and Windows |
| PORT_IDF_STM32CUBE | Bare-Metal (IDF) | STM32CubeMX based port | idf-stm32cube | XF for ARM Cortex based microcontrollers from STMicroelectronics  |
| PORT_STM32CUBE_CMSIS_FREERTOS | CMSIS OS (FreeRTOS) | Any platform supporting CMSIS OS | stm32cube-cmsis-freertos | FreeRTOS based port |