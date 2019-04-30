	Computer_System u0 (
		.acceleromter_control_I2C_SDAT      (<connected-to-acceleromter_control_I2C_SDAT>),      // acceleromter_control.I2C_SDAT
		.acceleromter_control_I2C_SCLK      (<connected-to-acceleromter_control_I2C_SCLK>),      //                     .I2C_SCLK
		.acceleromter_control_G_SENSOR_CS_N (<connected-to-acceleromter_control_G_SENSOR_CS_N>), //                     .G_SENSOR_CS_N
		.acceleromter_control_G_SENSOR_INT  (<connected-to-acceleromter_control_G_SENSOR_INT>),  //                     .G_SENSOR_INT
		.arduino_gpio_export                (<connected-to-arduino_gpio_export>),                //         arduino_gpio.export
		.arduino_reset_n_export             (<connected-to-arduino_reset_n_export>),             //      arduino_reset_n.export
		.expansion_jp1_export               (<connected-to-expansion_jp1_export>),               //        expansion_jp1.export
		.hex3_hex0_export                   (<connected-to-hex3_hex0_export>),                   //            hex3_hex0.export
		.hex5_hex4_export                   (<connected-to-hex5_hex4_export>),                   //            hex5_hex4.export
		.leds_export                        (<connected-to-leds_export>),                        //                 leds.export
		.pushbuttons_export                 (<connected-to-pushbuttons_export>),                 //          pushbuttons.export
		.sdram_addr                         (<connected-to-sdram_addr>),                         //                sdram.addr
		.sdram_ba                           (<connected-to-sdram_ba>),                           //                     .ba
		.sdram_cas_n                        (<connected-to-sdram_cas_n>),                        //                     .cas_n
		.sdram_cke                          (<connected-to-sdram_cke>),                          //                     .cke
		.sdram_cs_n                         (<connected-to-sdram_cs_n>),                         //                     .cs_n
		.sdram_dq                           (<connected-to-sdram_dq>),                           //                     .dq
		.sdram_dqm                          (<connected-to-sdram_dqm>),                          //                     .dqm
		.sdram_ras_n                        (<connected-to-sdram_ras_n>),                        //                     .ras_n
		.sdram_we_n                         (<connected-to-sdram_we_n>),                         //                     .we_n
		.sdram_clk_clk                      (<connected-to-sdram_clk_clk>),                      //            sdram_clk.clk
		.servo_1_control_export             (<connected-to-servo_1_control_export>),             //      servo_1_control.export
		.servo_2_control_export             (<connected-to-servo_2_control_export>),             //      servo_2_control.export
		.slider_switches_export             (<connected-to-slider_switches_export>),             //      slider_switches.export
		.system_pll_ref_clk_clk             (<connected-to-system_pll_ref_clk_clk>),             //   system_pll_ref_clk.clk
		.system_pll_ref_reset_reset         (<connected-to-system_pll_ref_reset_reset>),         // system_pll_ref_reset.reset
		.camera_control_sda_in              (<connected-to-camera_control_sda_in>),              //       camera_control.sda_in
		.camera_control_scl_in              (<connected-to-camera_control_scl_in>),              //                     .scl_in
		.camera_control_sda_oe              (<connected-to-camera_control_sda_oe>),              //                     .sda_oe
		.camera_control_scl_oe              (<connected-to-camera_control_scl_oe>)               //                     .scl_oe
	);

