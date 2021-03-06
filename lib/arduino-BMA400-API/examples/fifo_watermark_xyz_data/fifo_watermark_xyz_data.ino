/*Copyright (C) 2021 Telit Communications S.p.A. Italy - All Rights Reserved.*/
/*    See LICENSE file in the root folder for full license information.     */

/*!
 * @ingroup bma400Examples
 * @defgroup bma400ExamplesFifo FIFO watermark read
 * @brief Read and extract FIFO watermark data
 * \include fifo_watermark_xyz_data.ino
 */

#include <telit_bma400.h>

/* Earth's gravity in m/s^2 */
#define GRAVITY_EARTH   (9.80665f)

/* Total number of frames */
#define N_FRAMES       200

/* Add extra bytes to get complete fifo data */
#define FIFO_SIZE      (N_FRAMES + BMA400_FIFO_BYTES_OVERREAD)

static float lsb_to_ms2(int16_t accel_data, uint8_t g_range, uint8_t bit_width);


void setup() {

  int8_t rslt;

  uint16_t index;

    struct bma400_sensor_data accel_data[N_FRAMES] = { { 0 } };
    struct bma400_int_enable int_en;
    struct bma400_fifo_data fifo_frame;
    struct bma400_device_conf fifo_conf;
    struct bma400_sensor_conf conf;
    uint16_t int_status = 0;
    uint8_t fifo_buff[FIFO_SIZE] = { 0 };
    uint16_t accel_frames_req = N_FRAMES;
    float x, y, z;
    uint8_t try_count = 1;

  struct bma400_dev bma;
  
  Serial.begin(115200);
  delay(1000);


  rslt = bma400_interface_init(&bma, BMA400_I2C_INTF);
  bma400_check_rslt("bma400_interface_init", rslt);

  Serial.println("Read FIFO watermark interrupt XYZ data");

  rslt = bma400_soft_reset(&bma);
  bma400_check_rslt("bma400_soft_reset", rslt);

  rslt = bma400_init(&bma);
  bma400_check_rslt("bma400_init", rslt);

  /* Select the type of configuration to be modified */
  conf.type = BMA400_ACCEL;

  /* Get the accelerometer configurations which are set in the sensor */
  rslt = bma400_get_sensor_conf(&conf, 1, &bma);
  bma400_check_rslt("bma400_get_sensor_conf", rslt);

  /* Modify the desired configurations as per macros
   * available in bma400_defs.h file */
  conf.param.accel.odr = BMA400_ODR_100HZ;
  conf.param.accel.range = BMA400_RANGE_2G;
  conf.param.accel.data_src = BMA400_DATA_SRC_ACCEL_FILT_1;

  /* Set the desired configurations to the sensor */
  rslt = bma400_set_sensor_conf(&conf, 1, &bma);
  bma400_check_rslt("bma400_set_sensor_conf", rslt);

  fifo_conf.type = BMA400_FIFO_CONF;

  rslt = bma400_get_device_conf(&fifo_conf, 1, &bma);
  bma400_check_rslt("bma400_get_device_conf", rslt);

  fifo_conf.param.fifo_conf.conf_regs = BMA400_FIFO_X_EN | BMA400_FIFO_Y_EN | BMA400_FIFO_Z_EN;
  fifo_conf.param.fifo_conf.conf_status = BMA400_ENABLE;
  fifo_conf.param.fifo_conf.fifo_watermark = 200;
  fifo_conf.param.fifo_conf.fifo_wm_channel = BMA400_INT_CHANNEL_2;

  rslt = bma400_set_device_conf(&fifo_conf, 1, &bma);
  bma400_check_rslt("bma400_set_device_conf", rslt);

  rslt = bma400_set_power_mode(BMA400_MODE_NORMAL, &bma);
  bma400_check_rslt("bma400_set_power_mode", rslt);

  fifo_frame.data = fifo_buff;
  fifo_frame.length = FIFO_SIZE;

  int_en.type = BMA400_FIFO_WM_INT_EN;
  int_en.conf = BMA400_ENABLE;

  rslt = bma400_enable_interrupt(&int_en, 1, &bma);
  bma400_check_rslt("bma400_enable_interrupt", rslt);


  while (try_count <= 25)
  {
    rslt = bma400_get_interrupt_status(&int_status, &bma);
    bma400_check_rslt("bma400_get_interrupt_status", rslt);

    if (int_status & BMA400_ASSERTED_FIFO_WM_INT)
    {
      Serial.print("\n\nIteration : ");
      Serial.println(try_count);

      Serial.print("Requested FIFO length : ");
      Serial.println(fifo_frame.length);

      rslt = bma400_get_fifo_data(&fifo_frame, &bma);
      bma400_check_rslt("bma400_get_fifo_data", rslt);

      Serial.print("Available FIFO length : ");
      Serial.println(fifo_frame.length);

      accel_frames_req = N_FRAMES;
      rslt = bma400_extract_accel(&fifo_frame, accel_data, &accel_frames_req, &bma);
      bma400_check_rslt("bma400_extract_accel", rslt);

      if (accel_frames_req)
      {
        Serial.print("Extracted FIFO frames : ");
        Serial.println(accel_frames_req);

        Serial.println("Accel data in LSB units and Gravity data in m/s^2");

        for (index = 0; index < accel_frames_req; index++)
        {
          /* 12-bit accelerometer at range 2G */
          Serial.print("Accel[");
          Serial.print(index);
          Serial.print("] X : ");
          Serial.print(accel_data[index].x);
          Serial.print(" raw LSB    Y : ");
          Serial.print(accel_data[index].y);
          Serial.print(" raw LSB    Z : ");
          Serial.print(accel_data[index].z);
          Serial.println(" raw LSB");
          
          /* 12-bit accelerometer at range 2G */
          x = lsb_to_ms2(accel_data[index].x, 2, 12);
          y = lsb_to_ms2(accel_data[index].y, 2, 12);
          z = lsb_to_ms2(accel_data[index].z, 2, 12);

          /* Print the data in m/s2. */
          Serial.print("\t  Gravity-x = ");
          Serial.print(x);
          Serial.print(", Gravity-y = ");
          Serial.print(y);
          Serial.print(", Gravity-z = ");
          Serial.println(z);
        }
      }

      if (fifo_frame.conf_change)
      {
        Serial.print("FIFO configuration change: ");
        Serial.println(fifo_frame.conf_change);

        if (fifo_frame.conf_change & BMA400_FIFO_CONF0_CHANGE)
        {
          Serial.println("FIFO data source configuration changed");
        }

        if (fifo_frame.conf_change & BMA400_ACCEL_CONF0_CHANGE)
        {
          Serial.println("Accel filt1_bw configuration changed");
        }

        if (fifo_frame.conf_change & BMA400_ACCEL_CONF1_CHANGE)
        {
          Serial.println("Accel odr/osr/range configuration changed");
        }
      }
      try_count++;
    }
    delay(100);
  }

}

void loop() {
}



static float lsb_to_ms2(int16_t accel_data, uint8_t g_range, uint8_t bit_width)
{
    float accel_ms2;
    int16_t half_scale;

    half_scale = 1 << (bit_width - 1);
    accel_ms2 = (GRAVITY_EARTH * accel_data * g_range) / half_scale;

    return accel_ms2;

}
