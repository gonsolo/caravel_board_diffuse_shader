/*
 * If flashing doesn't work anymore:
 * This is the standard issue where if you flash a program that reconfigures GPIOs 1 to 4, then you
 * can no longer access the housekeeping SPI once the program has started.  The trick is to prevent
 * the program from starting.  Hold down the reset button, then power cycle the board while still
 * holding down the reset button, then run "make flash".  After the script says that the flash chip
 * is being erased, you can let go of the reset button. If your program keeps GPIOs 1 to 4 in their
 * original configuration that is compatible with the housekeeping SPI operation, then you won't
 * have this problem.  If your project requires use of GPIO 1 to 4, then this becomes a necessary
 * inconvenience every time you want to flash a new program.
 */

#include <defs.h>

void dummyDelay(int num)
{
        for (int i=0;i < num;i++){
                #ifdef ARM
                reg_wb_enable = reg_wb_enable;
                #endif //ARM
                continue;
        }
}

#define REG_GPIO_INVERTED 1

void ManagmentGpio_outputEnable()
{
        reg_gpio_mode1 = 1;
        reg_gpio_mode0 = 0; // for full swing
#ifndef REG_GPIO_INVERTED
        reg_gpio_ien = 0;
        reg_gpio_oeb = 1;
#else
        reg_gpio_ien = 1; // because in gf the GPIO enable regs are inverted
        reg_gpio_oeb = 0;
#endif
        dummyDelay(1);
}

void ManagmentGpio_write(bool data)
{
        reg_gpio_out = data;
}

void enableHkSpi(bool is_enable){
        reg_hkspi_disable = !is_enable;
}

void GPIOs_configure(int gpio_num, int config)
{
        switch(gpio_num){
                case 0 :
                        reg_mprj_io_0   = config; break;
                case 1 :
                        reg_mprj_io_1   = config; break;
                case 2 :
                        reg_mprj_io_2   = config; break;
                case 3 :
                        reg_mprj_io_3   = config; break;
                case 4 :
                        reg_mprj_io_4   = config; break;
                case 5 :
                        reg_mprj_io_5   = config; break;
                case 6 :
                        reg_mprj_io_6   = config; break;
                case 7 :
                        reg_mprj_io_7   = config; break;
                case 8 :
                        reg_mprj_io_8   = config; break;
                case 9 :
                        reg_mprj_io_9   = config; break;
                case 10:
                        reg_mprj_io_10  = config; break;
                case 11:
                        reg_mprj_io_11  = config; break;
                case 12:
                        reg_mprj_io_12  = config; break;
                case 13:
                        reg_mprj_io_13  = config; break;
                case 14:
                        reg_mprj_io_14  = config; break;
                case 15:
                        reg_mprj_io_15  = config; break;
                case 16:
                        reg_mprj_io_16  = config; break;
                case 17:
                        reg_mprj_io_17  = config; break;
                case 18:
                        reg_mprj_io_18  = config; break;
                case 19:
                        reg_mprj_io_19  = config; break;
                case 20:
                        reg_mprj_io_20  = config; break;
                case 21:
                        reg_mprj_io_21  = config; break;
                case 22:
                        reg_mprj_io_22  = config; break;
                case 23:
                        reg_mprj_io_23  = config; break;
                case 24:
                        reg_mprj_io_24  = config; break;
                case 25:
                        reg_mprj_io_25  = config; break;
                case 26:
                        reg_mprj_io_26  = config; break;
                case 27:
                        reg_mprj_io_27  = config; break;
                case 28:
                        reg_mprj_io_28  = config; break;
                case 29:
                        reg_mprj_io_29  = config; break;
                case 30:
                        reg_mprj_io_30  = config; break;
                case 31:
                        reg_mprj_io_31  = config; break;
                case 32:
                        reg_mprj_io_32  = config; break;
                case 33:
                        reg_mprj_io_33  = config; break;
                case 34:
                        reg_mprj_io_34  = config; break;
                case 35:
                        reg_mprj_io_35  = config; break;
                case 36:
                        reg_mprj_io_36  = config; break;
                case 37:
                        reg_mprj_io_37  = config; break;
                default:
                        break;
        }
}

void GPIOs_loadConfigs(){
        reg_mprj_xfer = 1;
        while ((reg_mprj_xfer & 0x1) == 1)
                // nix                
                ;
}

void configure_io()
{
            reg_mprj_io_0 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

            reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_2 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
            reg_mprj_io_3 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
            reg_mprj_io_4 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
 
            reg_mprj_io_5 = GPIO_MODE_USER_STD_OUTPUT; // output bit
            reg_mprj_io_6 = GPIO_MODE_USER_STD_OUTPUT; // output bit
            reg_mprj_io_7 = GPIO_MODE_USER_STD_OUTPUT; // output bit
            reg_mprj_io_8 = GPIO_MODE_USER_STD_OUTPUT; // output bit
            reg_mprj_io_9 = GPIO_MODE_USER_STD_OUTPUT; // output bit
            reg_mprj_io_10 = GPIO_MODE_USER_STD_OUTPUT; // output bit
            reg_mprj_io_11 = GPIO_MODE_USER_STD_OUTPUT; // output bit
            reg_mprj_io_12 = GPIO_MODE_USER_STD_OUTPUT; // output bit
 
            reg_mprj_io_13 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
            reg_mprj_io_14 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
            reg_mprj_io_15 = GPIO_MODE_MGMT_STD_INPUT_PULLDOWN;
 
            reg_mprj_io_16 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // input bit 7 (most significant)
            reg_mprj_io_17 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // input bit 6
            reg_mprj_io_18 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // input bit 5
            reg_mprj_io_19 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // input bit 4
            reg_mprj_io_20 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // input bit 3
            reg_mprj_io_21 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // input bit 2
            reg_mprj_io_22 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // input bit 1
            reg_mprj_io_23 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // input bit 0 (least significant)
 
            reg_mprj_io_24 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // byte 1
            reg_mprj_io_25 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // byte 0
 
            reg_mprj_io_26 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // channel 1
            reg_mprj_io_27 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // channel 0
 
            reg_mprj_io_28 = GPIO_MODE_USER_STD_INPUT_PULLDOWN; // Write
 
            reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
            reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
 
            // Initiate the serial transfer to configure IO
            reg_mprj_xfer = 1;
            while (reg_mprj_xfer == 1)
                    // wait
                    ;
}

void delay(const int d)
{
        /* Configure timer for a single-shot countdown */
	reg_timer0_config = 0;
	reg_timer0_data = d;
        reg_timer0_config = 1;

        // Loop, waiting for value to reach zero
        reg_timer0_update = 1;  // latch current value
        while (reg_timer0_value > 0) {
                reg_timer0_update = 1;
        }
}

void main()
{
        //int i, j, k;

#if 0
        ManagmentGpio_outputEnable();
        ManagmentGpio_write(0);
        enableHkSpi(0);

        for (int i = 5; i < 13; i++) {
                GPIOs_configure(i, GPIO_MODE_USER_STD_OUTPUT);
        }
        for (int i = 13; i < 21; i++) {
                GPIOs_configure(i, GPIO_MODE_MGMT_STD_INPUT_PULLDOWN);
        }
        for (int i = 21; i < 29; i++) {
                GPIOs_configure(i, GPIO_MODE_MGMT_STD_INPUT_PULLDOWN);
        }

        GPIOs_loadConfigs();
        ManagmentGpio_write(1);
#endif

        //reg_gpio_mode1 = 1;
        //reg_gpio_mode0 = 0;
        //reg_gpio_ien = 1;
        //reg_gpio_oeb = 1;

        //configure_io();

        // reg_uart_enable = 1;

        // Configure All LA probes as inputs to the cpu
	//reg_la0_oenb = reg_la0_iena = 0x00000000;    // [31:0]
	//reg_la1_oenb = reg_la1_iena = 0x00000000;    // [63:32]
	//reg_la2_oenb = reg_la2_iena = 0x00000000;    // [95:64]
	//reg_la3_oenb = reg_la3_iena = 0x00000000;    // [127:96]

	// write data to la output
        // reg_la0_data = 0x00;
        // reg_la1_data = 0x00;
        // reg_la2_data = 0x00;
        // reg_la3_data = 0x00;

        // read data from la input
        //	data0 = reg_la0_data;
        //	data1 = reg_la1_data;
        //	data2 = reg_la2_data;
        //	data3 = reg_la3_data;

        // print("Hello World !!");

	//while (1) {

        //        reg_gpio_out = 1; // OFF
        //        reg_mprj_datah = 0x0000002a;
        //        reg_mprj_datal = 0xaaaaaaaa;

	//	delay(4000000);

        //        reg_gpio_out = 0;  // ON
        //        reg_mprj_datah = 0x00000015;
        //        reg_mprj_datal = 0x55555555;

	//	delay(4000000);
        //}
}

