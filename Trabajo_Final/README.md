# Trabajo Final - Réplica paper: gSLICr: SLIC superpixels at over 250Hz
#### Slides
![LINK DE SLIDES](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/TCG_Final_slides.pdf)

#### Compilación en Colab
![LINK COLAB CODIGO](https://colab.research.google.com/drive/16aMj1P9Rou97qqvGb8hInIckub0_DF8s?usp=sharing)
#### Link de videos
- Video de 10 minutos: Explicación y ejecución detallada de codigo y slides: ![LINK DRIVE VIDEO](https://drive.google.com/file/d/1tT6tiJgn-EwvPq_JV6GF8VxS-2EPIs60/view?usp=sharing)
- Video de 2 minutos: Solo ejecución sin slides ni explicación de codigo: ![LINK DRIVE VIDEO](https://drive.google.com/file/d/1fgDZYfbbf3rLu_8L9yhVW2uHJ4rse4ee/view?usp=sharing)
## Requerimientos y dependencias
```bash
python3 (>=.5)
cmake (>= 2.8.10.2)
CUDA (>= 6.0)
OpenCV (>= 3.0)
```
## Construcción y ejecución (Colab)
```bash
mkdir build
cd build
cmake ../
make
python3 example.py
```
## Algoritmo
### Pipeline
El algoritmo utilizado se puede ver en 5 pasos
1. Conversión de el espacio de la imagen; se convierte a CIELAB
2. Inicialización del centro del cluster
3. Encontrar las asociaciones de cluster
4. Actualizar el centro del cluster
5. Forzar la conectividad
### Función General
```c
void seg_engine::Perform_Segmentation(UChar4Image* in_img)
{
	source_img->SetFrom(in_img, ORUtils::MemoryBlock<Vector4u>::CPU_TO_CUDA);
	Cvt_Img_Space(source_img, cvt_img, gSLICr_settings.color_space);

	Init_Cluster_Centers();
	Find_Center_Association();

	for (int i = 0; i < gSLICr_settings.no_iters; i++)
	{
		Update_Cluster_Center();
		Find_Center_Association();
	}

	if(gSLICr_settings.do_enforce_connectivity) Enforce_Connectivity();
	cudaThreadSynchronize();
}
```
## Pruebas
### Pruebas con imágenes de paper
#### Imagen de entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/InputImage/arequipa0_b.jpeg)
#### Imagen de salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/OutImages/arequipa0_a.jpeg)

### Pruebas ejecutadas (propias)
#### Imagen de Entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/InputImage/arequipa1_b.jpeg)
#### Imagen de salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/OutImages/arequipa1_a.jpeg)
#### Imagen de entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/InputImage/arequipa2_b.jpeg)
#### Imagen de salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/OutImages/arequipa2_a.jpeg)

#### Imagen de entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/InputImage/arequipa3_b.jpeg)
#### Imagen de salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/OutImages/arequipa3_a.jpeg)
#### Imagen de entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/InputImage/arequipa4_b.jpeg)
#### Imagen de salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Trabajo_Final/OutImages/arequipa4_a.jpeg)
