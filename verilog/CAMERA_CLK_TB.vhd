library ieee;
use ieee.std_logic_1164.all;

entity CAMERA_CLK_TB is
end entity CAMERA_CLK_TB;

architecture TESTBENCH of CAMERA_CLK_TB is

	component CAMERA_CLK_PSC is
	port(
			CLK_IN: in std_logic;
			CLK_OUT: out std_logic
		);
	end component CAMERA_CLK_PSC;
	
	signal CLK_IN,CLK_OUT : std_logic := '0';

	
	

begin 

	uut: CAMERA_CLK_PSC port map(CLK_IN=>CLK_IN,CLK_OUT=>CLK_OUT);
	
	
	 -- continuous clock
    process 
    begin
        CLK_IN <= '0';
        wait for 10ns;
        CLK_IN <= '1';
        wait for 10ns;
    end process;


end architecture TESTBENCH;