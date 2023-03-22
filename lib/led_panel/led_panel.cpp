#include <led_panel.h>

MatrixPanel_I2S_DMA *dma_display = nullptr;

void* setup_screen(){
    HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
    HUB75_I2S_CFG matrix_config(
        PANEL_RES_X,
        PANEL_RES_Y,
        PANEL_CHAIN,
        _pins
    );

    dma_display = new MatrixPanel_I2S_DMA(matrix_config);
    dma_display->begin();

    return dma_display;
}