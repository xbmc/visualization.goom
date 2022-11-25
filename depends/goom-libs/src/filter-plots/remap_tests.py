import numpy as np

if __name__ == "__main__":
    remap = {
            (0, 0): (2, 2),
            (0, 1): (2, 1),
            (0, 2): (2, 0),
            (1, 0): (1, 2),
            (1, 1): (1, 1),
            (1, 2): (1, 0),
            (2, 0): (0, 2),
            (2, 1): (1, 2),
            (2, 2): (0, 0),
    }
    image = np.array([
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9],
    ])

    remapped_image = image.copy()
    for k in remap:
        remapped_image[k[0], k[1]] = image[remap[k][0], remap[k][1]]

    print(image.shape)
    print(image)
    print(remapped_image)

#    for y in range(0, 3):
#        for x in range(0, 3):
#            print(image[x, y])
