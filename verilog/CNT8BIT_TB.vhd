library ieee;
use ieee.std_logic_1164.all;

entity CNT8BIT_TB is
end entity CNT8BIT_TB;

architecture TESTBENCH of CNT8BIT_TB is

	component CNT8BIT is
	port(
			CLK, RST, UP_DWN, LD, EN : in std_logic;
			COUNTIN : in std_logic_vector(7 downto 0);
			COUNTOUT : out std_logic_vector(7 downto 0)
		);
	end component CNT8BIT;
	
	signal CLK : std_logic := '0';
	signal RST : std_logic := '0';
	signal UP_DWN : std_logic := '0';
	signal LD : std_logic := '0';
	signal EN : std_logic := '0';
	signal COUNTIN : std_logic_vector(7 downto 0) := "00001000";
	
	signal COUNTOUT : std_logic_vector(7 downto 0) := "00000000";
	
	

begin 

	uut: CNT8BIT port map(CLK=>CLK,RST=>RST,UP_DWN=>UP_DWN,LD=>LD,EN=>EN,COUNTIN=>COUNTIN,COUNTOUT=>COUNTOUT);
	
	
	 -- continuous clock
    process 
    begin
        CLK <= '0';
        wait for 10ns;
        CLK <= '1';
        wait for 10ns;
    end process;
	 
	 RST <= '1', '0' after 15ns;
	 
	 LD <= '0', '1' after 30ns, '0' after 40ns;
	 
	 EN <= '0', '1' after 60ns;
	 
	 UP_DWN <= '0', '1' after 120ns;


end architecture TESTBENCH;