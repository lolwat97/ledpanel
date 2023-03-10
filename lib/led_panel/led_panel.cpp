#include <led_panel.h>

MatrixPanel_I2S_DMA *dma_display = nullptr;

void* setup_screen(){
    HUB75_I2S_CFG matrix_config(
        PANEL_RES_X,
        PANEL_RES_Y,
        PANEL_CHAIN
    );

    dma_display = new MatrixPanel_I2S_DMA(matrix_config);
    dma_display->begin();

    return dma_display;
}