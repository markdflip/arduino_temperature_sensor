import socket
import ConfigParser
import os


ROOT_FILE_PATH = os.path.dirname(os.path.realpath(__file__)) +"/"
config_file = ROOT_FILE_PATH + "arduino.conf"

print("Looking for configuration file at %s", config_file)

config = ConfigParser.ConfigParser()
config.read(config_file)

UDP_IP = config.get('Arduino_udp', 'UDP_IP')
UDP_PORT = int(config.get('Arduino_udp', 'UDP_PORT'))

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    print ("received message:", data)