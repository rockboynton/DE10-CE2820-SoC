-- Name: Draven Schilling
-- Course: CE 2820
-- Teacher: Dr. Livingston
-- Lab mileston 5 Camera
-- 4/24/19

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity CAMERA_CLK_PSC is
port(
		CLK_IN: in std_logic;
		CLK_OUT: out std_logic
	);
end entity CAMERA_CLK_PSC;

architecture BEHAV of CAMERA_CLK_PSC is

	signal COUNT : std_logic := '0';

begin

--update free running counter
	process(CLK_IN) is
	begin
		if rising_edge(CLK_IN) then
			if (COUNT = '1') then
				COUNT <= '0';
				CLK_OUT <= '1';
			else
				COUNT <= '1';
				CLK_OUT <= '0';
			end if;
		end if;
	end process;
	
end architecture BEHAV;




