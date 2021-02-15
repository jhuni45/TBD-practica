from skimage.io import imread

from gSLICrPy import __get_CUDA_gSLICr__, CUDA_gSLICr


def main(imagen):
    image = imread('./'+imagen+'.jpg')
    img_size_y, img_size_x = image.shape[0:2]
    image = image[:, :, ::-1].flatten().astype('uint8')

    __CUDA_gSLICr__ = __get_CUDA_gSLICr__()

    CUDA_gSLICr(__CUDA_gSLICr__,
                image,
                img_size_x=img_size_x,
                img_size_y=img_size_y,
                n_segs=10,
                spixel_size=15,
                coh_weight=0.6,
                n_iters=50,
                color_space=2,
                segment_color_space=2,
                segment_by_size=True,
                enforce_connectivity=True,
                out_name=imagen)


if __name__ == '__main__':
    main('catedral')
    main('catedral2')
    main('volcan')
    main('volcan2')
    main('oxford')
