
module Computer_System (
	acceleromter_control_I2C_SDAT,
	acceleromter_control_I2C_SCLK,
	acceleromter_control_G_SENSOR_CS_N,
	acceleromter_control_G_SENSOR_INT,
	arduino_gpio_export,
	arduino_reset_n_export,
	expansion_jp1_export,
	hex3_hex0_export,
	hex5_hex4_export,
	leds_export,
	pushbuttons_export,
	sdram_addr,
	sdram_ba,
	sdram_cas_n,
	sdram_cke,
	sdram_cs_n,
	sdram_dq,
	sdram_dqm,
	sdram_ras_n,
	sdram_we_n,
	sdram_clk_clk,
	servo_1_control_export,
	servo_2_control_export,
	slider_switches_export,
	system_pll_ref_clk_clk,
	system_pll_ref_reset_reset,
	camera_control_sda_in,
	camera_control_scl_in,
	camera_control_sda_oe,
	camera_control_scl_oe);	

	inout		acceleromter_control_I2C_SDAT;
	output		acceleromter_control_I2C_SCLK;
	output		acceleromter_control_G_SENSOR_CS_N;
	input		acceleromter_control_G_SENSOR_INT;
	inout	[15:0]	arduino_gpio_export;
	output		arduino_reset_n_export;
	inout	[31:0]	expansion_jp1_export;
	output	[31:0]	hex3_hex0_export;
	output	[15:0]	hex5_hex4_export;
	output	[9:0]	leds_export;
	input	[1:0]	pushbuttons_export;
	output	[12:0]	sdram_addr;
	output	[1:0]	sdram_ba;
	output		sdram_cas_n;
	output		sdram_cke;
	output		sdram_cs_n;
	inout	[15:0]	sdram_dq;
	output	[1:0]	sdram_dqm;
	output		sdram_ras_n;
	output		sdram_we_n;
	output		sdram_clk_clk;
	output	[7:0]	servo_1_control_export;
	output	[7:0]	servo_2_control_export;
	input	[9:0]	slider_switches_export;
	input		system_pll_ref_clk_clk;
	input		system_pll_ref_reset_reset;
	input		camera_control_sda_in;
	input		camera_control_scl_in;
	output		camera_control_sda_oe;
	output		camera_control_scl_oe;
endmodule
