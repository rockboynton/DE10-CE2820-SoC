-- Name: Rock Boynton
-- Course: CE 2820
-- Teacher: Dr. Livingston
-- Lab 3 Accelerometer Control Testbench
-- 4/8/19

library ieee;
use ieee.std_logic_1164.all;

entity AccelerometerControl_TB is
end entity AccelerometerControl_TB;

architecture TESTBENCH of AccelerometerControl_TB is

	component AccelerometerControl is
	port(
        CLK, MDI, RST    : in std_logic;
        CS , MDO, CLKOUT : out std_logic;
        X  , Y  , Z      : out std_logic_vector(9 downto 0)
		);
	end component AccelerometerControl;

	--create signals for each pin in the input/outputs
    signal CLK    : std_logic : = '0';
    signal MDI    : std_logic : = '0';
    signal RST    : std_logic : = '0';
    signal CS     : std_logic : = '0';
    signal MDO    : std_logic : = '0';
    signal CLKOUT : std_logic : = '0';
    signal X      : std_logic_vector(7 downto 0);
    signal Y      : std_logic_vector(7 downto 0);
    signal Z      : std_logic_vector(7 downto 0);

begin

    UUT: AccelerometerControl port map(
        CLK=>CLK
        MDI=>MDI
        RST=>RST
        CS=>CS
        MDO=>MDO
        CLKOUT=>CLKOUT
        X=>X
        Y=>Y
        Z=>Z
    );

    -- continuous 50MHz clock
    clock: process
    begin
        CLK <= '0';
        wait for 10ns;
        CLK <= '1';
        wait for 10ns;
    end process;

    tester: process
    begin
        -- test asynchronous, active low reset
        RST <= '0', '1' after 15ns;
        -- test accelerometer
        -- TODO
        -- CS - "This line must go low at the start of a transmission and high at the end of a transmission" - Pg. 14 Docs
        CS <= '1', '0' after 150ns;
        wait;
    end process tester;

end architecture TESTBENCH;
