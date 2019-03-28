-- Name: Draven Schilling
-- Course: CE 2820
-- Teacher: Dr. Livingston
-- Lab 3 Servo Testbench
-- 3/20/19

library ieee;
use ieee.std_logic_1164.all;

entity SERVO_TB is
end entity SERVO_TB;

architecture TESTBENCH of SERVO_TB is

	component Servo is
	port(
			CLK, RST: in std_logic;
			DB : in std_logic_vector(7 downto 0);
			PULSEOUT: out std_logic
		);
	end component Servo;
	
	--create signals for each pin in the input/outputs
	signal CLK : std_logic := '0';
	signal RST : std_logic := '0';
	signal DATA : std_logic_vector(7 downto 0);
	signal OUTPUT : std_logic := '0';
	
	

begin 

	uut: Servo port map(CLK=>CLK,RST=>RST,DB=>DATA,PULSEOUT=>OUTPUT);
	
	
	 -- continuous clock
    process 
    begin
        CLK <= '0';
        wait for 10ns;
        CLK <= '1';
        wait for 10ns;
    end process;
	 
	 RST <= '1', '0' after 15ns;
	 --switch from 0 to 100 after 1 cycle, then to 200 after another cycle and finally 255 
	 -- after that cycle
	 DATA <= "00000000", "01100100" after 20ms, "11001000" after 40ms, "11111111" after 60ms;


end architecture TESTBENCH;