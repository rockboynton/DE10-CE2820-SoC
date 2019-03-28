library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity CNT8BIT is
port(
		CLK, RST, UP_DWN, LD, EN : in std_logic;
		COUNTIN : in std_logic_vector(7 downto 0);
		COUNTOUT : out std_logic_vector(7 downto 0)
	);
end entity CNT8BIT;

architecture BEHAV of CNT8BIT is

	signal COUNT : integer range 0 to 255;

begin

	process(CLK, RST) is
	begin
	
		if (RST='1') then
			COUNT <= 0;
		elsif rising_edge(CLK) then
			if (LD = '1') then
				COUNT <= to_integer(unsigned(COUNTIN));
			elsif (EN = '1') then
				if (UP_DWN = '1') then
					COUNT <= COUNT + 1;
				else
					COUNT <= COUNT - 1;
				end if;
			end if;
		end if;
	end process;
	
	COUNTOUT <= std_logic_vector(to_unsigned(COUNT,8));


end architecture BEHAV;




