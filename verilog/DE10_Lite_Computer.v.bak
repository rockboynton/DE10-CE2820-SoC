

module DE10_Lite_Computer (
	// Clock pins
	CLOCK_50,
	CLOCK2_50,
	CLOCK_ADC_10,

	// ARDUINO
	ARDUINO_IO,
	ARDUINO_RESET_N,
	
	// SDRAM
	DRAM_ADDR,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_CKE,
	DRAM_CLK,
	DRAM_CS_N,
	DRAM_DQ,
	DRAM_LDQM,
	DRAM_RAS_N,
	DRAM_UDQM,
	DRAM_WE_N,

	// Accelerometer
	G_SENSOR_CS_N,
	G_SENSOR_INT,
	G_SENSOR_SCLK,
	G_SENSOR_SDI,
	G_SENSOR_SDO,
	
	// 40-Pin Headers
	GPIO,
	
	// Seven Segment Displays
	HEX0,
	HEX1,
	HEX2,
	HEX3,
	HEX4,
	HEX5,

	// Pushbuttons
	KEY,

	// LEDs
	LEDR,

	// Slider Switches
	SW,

	// VGA
	VGA_B,
	VGA_G,
	VGA_HS,
	VGA_R,
	VGA_VS
);

//=======================================================
//  PARAMETER declarations
//=======================================================


//=======================================================
//  PORT declarations
//=======================================================

// Clock pins
input						CLOCK_50;
input						CLOCK2_50;
input						CLOCK_ADC_10;

// ARDUINO
inout			[15: 0]	ARDUINO_IO;
inout						ARDUINO_RESET_N;
	
// SDRAM
output 		[12: 0]	DRAM_ADDR;
output		[ 1: 0]	DRAM_BA;
output					DRAM_CAS_N;
output					DRAM_CKE;
output					DRAM_CLK;
output					DRAM_CS_N;
inout			[15: 0]	DRAM_DQ;
output					DRAM_LDQM;
output					DRAM_RAS_N;
output					DRAM_UDQM;
output					DRAM_WE_N;

// Accelerometer
output					G_SENSOR_CS_N;
input			[ 2: 1]	G_SENSOR_INT;
output					G_SENSOR_SCLK;
inout						G_SENSOR_SDI;
inout						G_SENSOR_SDO;
	
// 40-pin headers
inout			[35: 0]	GPIO;

// Seven Segment Displays
output		[ 7: 0]	HEX0;
output		[ 7: 0]	HEX1;
output		[ 7: 0]	HEX2;
output		[ 7: 0]	HEX3;
output		[ 7: 0]	HEX4;
output		[ 7: 0]	HEX5;

// Pushbuttons
input			[ 1: 0]	KEY;

// LEDs
output		[ 9: 0]	LEDR;

// Slider Switches
input			[ 9: 0]	SW;

// VGA
output		[ 3: 0]	VGA_B;
output		[ 3: 0]	VGA_G;
output					VGA_HS;
output		[ 3: 0]	VGA_R;
output					VGA_VS;

//=======================================================
//  REG/WIRE declarations
//=======================================================

wire			[31: 0]	hex3_hex0;
wire			[15: 0]	hex5_hex4;

assign HEX0 = ~hex3_hex0[ 7: 0];
assign HEX1 = ~hex3_hex0[15: 8];
assign HEX2 = ~hex3_hex0[23:16];
assign HEX3 = ~hex3_hex0[31:24];
assign HEX4 = ~hex5_hex4[ 7: 0];
assign HEX5 = ~hex5_hex4[15: 8];

//=======================================================
//  Structural coding
//=======================================================

Computer_System The_System (
	////////////////////////////////////
	// FPGA Side
	////////////////////////////////////

	// Global signals
	.system_pll_ref_clk_clk					(CLOCK_50),
	.system_pll_ref_reset_reset			(1'b0),
	.video_pll_ref_clk_clk			(CLOCK2_50),
	.video_pll_ref_reset_reset		(1'b0),

	// Arduino GPIO
	.arduino_gpio_export						(ARDUINO_IO),

	// Arduino Reset_n
	.arduino_reset_n_export					(ARDUINO_RESET_N),

	// Slider Switches
	.slider_switches_export					(SW),

	// Pushbuttons
	.pushbuttons_export						(~KEY[1:0]),

	// Expansion JP1
	.expansion_jp1_export					({GPIO[35:19], GPIO[17], GPIO[15:3], GPIO[1]}),

	// LEDs
	.leds_export								(LEDR),
	
	// Seven Segs
	.hex3_hex0_export							(hex3_hex0),
	.hex5_hex4_export							(hex5_hex4),
	
	// VGA Subsystem
	.vga_CLK										(),
	.vga_BLANK									(),
	.vga_SYNC									(),
	.vga_HS										(VGA_HS),
	.vga_VS										(VGA_VS),
	.vga_R										(VGA_R),
	.vga_G										(VGA_G),
	.vga_B										(VGA_B),
	
	// SDRAM
	.sdram_clk_clk								(DRAM_CLK),
	.sdram_addr									(DRAM_ADDR),
	.sdram_ba									(DRAM_BA),
	.sdram_cas_n								(DRAM_CAS_N),
	.sdram_cke									(DRAM_CKE),
	.sdram_cs_n									(DRAM_CS_N),
	.sdram_dq									(DRAM_DQ),
	.sdram_dqm									({DRAM_UDQM,DRAM_LDQM}),
	.sdram_ras_n								(DRAM_RAS_N),
	.sdram_we_n									(DRAM_WE_N),
	
	// the Accelerometer
	.accelerometer_I2C_SDAT				(G_SENSOR_SDI),
	.accelerometer_I2C_SCLK				(G_SENSOR_SCLK),
	.accelerometer_G_SENSOR_CS_N		(G_SENSOR_CS_N),
	.accelerometer_G_SENSOR_INT		(G_SENSOR_INT)
);


endmodule
