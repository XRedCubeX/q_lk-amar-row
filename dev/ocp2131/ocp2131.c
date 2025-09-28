#include <platform/upmu_common.h>
#include <platform/upmu_hw.h>
#include <platform/mt_gpio.h>
#include <platform/mt_i2c.h>
#include <platform/mt_pmic.h>
#include "ocp2131.h"

#define GPIO_LCD_BIAS_ENP_PIN   167
#define GPIO_LCD_BIAS_ENN_PIN   168
#define I2C_I2C_LCD_BIAS_CHANNEL 6
#define OCP2131_SLAVE_ADDR_WRITE    0x3E

struct i2c_client *ocp2131_i2c_client;

void OCP2131_GPIO_ENP_enable(void)
{
    mt_set_gpio_out(GPIO_LCD_BIAS_ENP_PIN, 1);
}

void OCP2131_GPIO_ENN_enable(void)
{
    mt_set_gpio_out(GPIO_LCD_BIAS_ENN_PIN, 1);
}

void OCP2131_GPIO_ENP_disable(void)
{
    mt_set_gpio_out(GPIO_LCD_BIAS_ENP_PIN, 0);
}

void OCP2131_GPIO_ENN_disable(void)
{
    mt_set_gpio_out(GPIO_LCD_BIAS_ENN_PIN, 0);
}

static struct mt_i2c_t OCP2131_i2c;

int OCP2131_write_bytes(kal_uint8 addr, kal_uint8 value)
{
    kal_uint32 ret_code = I2C_OK;
    kal_uint8 write_data[2];
    kal_uint16 len;
    write_data[0]= addr;
    write_data[1] = value;
    OCP2131_i2c.id = I2C_I2C_LCD_BIAS_CHANNEL;
    OCP2131_i2c.addr = (OCP2131_SLAVE_ADDR_WRITE >> 1);
    OCP2131_i2c.mode = ST_MODE;
    OCP2131_i2c.speed = 100;
    len = 2;
    ret_code = i2c_write(&OCP2131_i2c, write_data, len);
    printf("%s: i2c_write: addr:0x%x, value:0x%x ret_code: %d\n", __func__, addr, value, ret_code);
    return ret_code;
}
