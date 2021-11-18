# IC
Iremos colocar aqui todos os nossos projetos de IC

## Contribuidores
- [João Fernandes](https://github.com/GilFernandes2000)
- [João Martins](https://github.com/jfngsea)
- [Miguel Ferreira](https://github.com/mgLTF)
  
## Indice:
- [IC](#ic)
  - [Contribuidores](#contribuidores)
  - [Indice:](#indice)
- [Project 1](#project-1)
  - [Ficheiros necessarios](#ficheiros-necessarios)
    - [Biblioteca de Audio](#biblioteca-de-audio)
    - [OpenCV](#opencv)
  - [Argumentos necessários para cada ficheiro](#argumentos-necessários-para-cada-ficheiro)

# Project 1
Primeiro projeto onde manipulamos texto, audio e imagens


## Ficheiros necessarios
Todos os ficheiros levam argumentos para poderem ser executados corretamente
### Biblioteca de Audio

[AudioFile.h](https://github.com/GilFernandes2000/IC-projects/blob/main/Project1/AudioFile.h)

### OpenCV
Criar um ficheiro CMake.txt com este codigo no diretorio do codigo a correr 
````
include(CTest)
enable_testing()

find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DRIS} )

add_executable(IC-Projects FILENAME.cpp) 

target_link_libraries( ICProjects ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
````
Substitur o **FILENAME** pelo nome do ficheiro a executar 

## Argumentos necessários para cada ficheiro
Começar sempre com
````
cd build\Debug
````
- Ex2:
  ````
  IC-Projects.exe <TextFile> <OutputFile>
  ````
- Ex3:
  ````
  IC-Projects.exe <InputAudio>
  ````
- Ex4:
  ````
  IC-Projects.exe <ImageFile>
  ````
- Ex5:
  ````
  IC-Projects.exe <TextFile> <HistogramFile>
  ````
- Ex6:
  ````
  IC-Projects.exe <AudioFile>
  ````
- Ex7:
  ````
  IC-Projects.exe <ImageFile>
  ````
- Ex8:
  ````
  IC-Projects.exe <AudioFile> <QuantizationFactor>
  ````
- Ex9:
  ````
  IC-Projects.exe <ImageFile> <DivisionFactor>
  ````
- Ex10:
  ````
  IC-Projects.exe <Reference AudioFile> <Quantized AudioFile> <QuantizationFactor>
  ````
- Ex11:
  ````
  IC-Projects.exe <ImageFile> <ImageFile>
  ````
