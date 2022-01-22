# IC
Iremos colocar aqui todos os nossos projetos de IC

## Contribuidores
- [João Fernandes, 93460](https://github.com/GilFernandes2000)
- [João Martins, 93183](https://github.com/jfngsea)
- [Miguel Ferreira, 93419](https://github.com/mgLTF)
  
## Indice:
- [IC](#ic)
  - [Contribuidores](#contribuidores)
  - [Indice:](#indice)
- [Projeto 1](#projeto-1)
  - [Bibliotecas Usadas](#bibliotecas-usadas)
    - [Boost 1.78 (https://www.boost.org/)](#boost-178-httpswwwboostorg)
    - [Biblioteca de Audio](#biblioteca-de-audio)
    - [OpenCV](#opencv)
  - [Argumentos necessários para cada ficheiro](#argumentos-necessários-para-cada-ficheiro)
- [Projeto 2](#projeto-2)
  - [Ficheiros necessarios](#ficheiros-necessarios)
    - [Biblioteca de Audio](#biblioteca-de-audio-1)
    - [OpenCV](#opencv-1)
  - [Argumentos](#argumentos)
  - [Documentação](#documentação)
- [Projeto 3](#projeto-3)

# Projeto 1
Primeiro projeto onde manipulamos texto, audio e imagens \
[**Relatorio**](https://github.com/GilFernandes2000/IC-projects/blob/main/Project1/Project1_IC.pdf)  


## Bibliotecas Usadas
Todos os ficheiros levam argumentos para poderem ser executados corretamente
### Boost 1.78 (https://www.boost.org/)
Incluida na pasta lib, nã havendo assim necessidade de qualquer instalação.

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


# Projeto 2
Projeto onde condificamos imagens e audio com base no algoritmo de Golomb\
[**Relatorio**](https://github.com/GilFernandes2000/IC-projects/blob/main/Project1/Project1_IC.pdf)  


## Ficheiros necessarios
Todos os ficheiros levam argumentos para poderem ser executados corretamente
### Biblioteca de Audio

[AudioFile.h](https://github.com/GilFernandes2000/IC-projects/blob/main/Project1/AudioFile.h)



### OpenCV
Criar um ficheiro CMake.txt com este codigo no diretorio do codigo a correr


````
cmake_minimum_required(VERSION 3.0.0)
project(Project2 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/test)

#AudioFile.h and Boost 1.78
include_directories(${CMAKE_SOURCE_DIR}/lib)

#OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Project2 src/main.cpp src/AudioEncoder.cpp src/AudioEncoder.h src/AudioPredictor.cpp src/AudioPredictor.h src/ImagePredictor.h src/ImagePredictor.cpp src/ImageEncoder.h src/ImageEncoder.cpp)
target_link_libraries( Project2 ${OpenCV_LIBS} )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
````
## Argumentos 
- Audio Encoding:
  ````
  <exe> audio encode <input_file_path> <output_file_path>
  ````
- Audio Decoding:
  ````
  <exe> audio decode <input_file_path> <output_file_path>
  ````
- Image Encoding:
  ````
  <exe> image encode <image_path> <output_file_path> <encoding_format> <predictor> <mode> <quantetization_factor>
  ````
Se **enconding_format = "lossy"** deve escolher um valor para a **quantetization_factor**. \
Se **predictor = "linear"** deve escolher um valor, de **1 a 7** para o **mode**. \
Ambos o **mode** e **quantetization_factor** têm valores predefinidos (1 e 0 respetivamente).

## Documentação
Para gerar a documentação:
````
cd Project2
Doxyfile
````
# Projeto 3
[**Relatorio**](#)

## Executaveis
Foram desenvolvidos N executaveis:
### FCM
 ````
  fcm <language> <context_order> <smoothing_parameter>
 ````
 Permite o treino de modelos de contexto finito para ficheiros de texto.
 
 De forma a gerar um modelo (de probabilidades) é usado um contador das diversas ocorrencias (contexto, carater), no entanto, ambas usam a mesma estrutura genérica internamente:
 ````
  using MODEL = std::map<std::string, std::map<std::string , T>>;
 ````
 com um datapath:
 ````
  Ficheiro de Texto ---> Contador (ocurrencias) [FCModelFactory.h] ---> Modelo (probabilidades) [FCModel.h]
 ````
 
 O executavel tem de ser executado com os parametros acima mencionados pois são necessarios para criar um contador inicial, no entato o programa permite fazer o _load_ de um ficheiro com um contador já pre-preeenchido para continuar o treino no entanto este substituirá o contador inicial. 
 
 O programa aresenta ainda um menu interno que permite operações sobre contadores/modelos:
 - ler um ficheiro de texto para atualizar os contadores
 - guardar o estado atual dos contadores;
 - fazer o  _load_ do estado dos contadores aprtir de um ficheiro
 - criar um modelo de probabilidadeds e guarda-lo num ficheiro (apresenta a entropia do modelo);
 - _load_ de um modelo de probabilidades e calcular a entropia.
  
 #### Parametros
 - language: a lingua dos ficheiros de texto que serão usados para treinar o modelo, serve apenas como _label_ e portanto é deixado a descriçao do utilzador a correção entre o parametro e os ficheiros efetivamente usados.
 - context_order: número de caracteres que serão usados para contexto.
 - smoothing_parameter: smoothin na fórmula de Lapalce de forma a lidar com a existencia de probabilidades nulas.

