#############
#
# ImperadorTelemetria.py
# Escrito para rodar no Windows 11
#
#
# Autor: Rafael Eijy Ishikawa Rasoto - Lambari
#
###########

import tkinter
import os
from PIL import Image, ImageTk
import serial.tools.list_ports
import threading
import continuous_threading
import datetime
import numpy
import matplotlib.pyplot as plt
from drawnow import *
import pandas as pd






###### Variáveis

serialInst = serial.Serial()

ports = serial.tools.list_ports.comports()
portList = []

for onePort in ports:
    portList.append(str(onePort))

statusConexao = False
baudrate = 9600


velocidadeAtual = 0
rpmAtual = 0
freioAtual  = False
temperaturaAtual = False
bateriaAtual = False




###### Eventos

def eventoSelectBaudRate(baudRate_recebido):
   
    baudRate_recebido = varBaudRate.get()
    print("Baud Rate recebido: " + baudRate_recebido)

    global baudrate
    baudrate = baudRate_recebido
    print("Variável BaudRate: " + str(baudrate))

    return
    


def eventoSelectCOM(COM_recebido):
    
    COM_recebido = varPortaCOM.get()
    print("Porta COM recebida: " + COM_recebido)

    global portaCOM
    
    for i in range(0, len(portList)):
        if portList[i] == COM_recebido:
            print("COM recebida" + portList[i][0:4])
            portaCOM = portList[i][0:4]

    return


def eventoBotaoConectar():
    global statusConexao
    
    if statusConexao == False:
        
        statusConexao = True
        conectarBotao.configure(text="Desconectar")
        statusConexaoLabel.configure(text="Conectado", bg="green")
        serialInst.baudrate = baudrate
        serialInst.port = portaCOM
        serialInst.open()

        return
    
    statusConexao = False
    conectarBotao.configure(text="Conectar")
    statusConexaoLabel.configure(text="Desconectado", bg = "red")
    serialInst.close()

    return

def eventoBotaoApagar():
    textoRecebido.delete("0.0", "end")
    return

def eventoBotaoEnviar():
    print("Enviar")




###### JANELA PRINCIPAL

janela = tkinter.Tk()
janela.geometry("1280x720")
janela.title("Imperador - Telemetria")
janela.grid_rowconfigure(0, weight=1)
janela.grid_columnconfigure(1, weight=1)





###### FONTES

fonteTitulo = ("Impact", 20, "bold")
fonteBotao = ("Oswald", 20)
fonteTexto = ("Oswald", 12)





###### IMAGENS 

image_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "imgs")

imagemLogo          = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Logo.png")).resize((200,100), Image.Resampling.LANCZOS))
imagemConexao       = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Conexao.png")).resize((50,50), Image.Resampling.LANCZOS))
imagemTelemetria    = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Telemetria.png")).resize((50,50), Image.Resampling.LANCZOS))
imagemLog           = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Log.png")).resize((50,50), Image.Resampling.LANCZOS))
imagemBorracha      = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Borracha.png")).resize((30,30), Image.Resampling.LANCZOS))
imagemFreio         = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Freio.png")).resize((50,50), Image.Resampling.LANCZOS))
imagemTemperatura   = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Temperatura.png")).resize((50,50), Image.Resampling.LANCZOS))
imagemBateria       = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Bateria.png")).resize((50,50), Image.Resampling.LANCZOS))
imagemVelocidade    = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Velocidade.png")).resize((50,50), Image.Resampling.LANCZOS))
imagemRpm           = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Rpm.png")).resize((50,50), Image.Resampling.LANCZOS))
imagemConectar      = ImageTk.PhotoImage(Image.open(os.path.join(image_path, "Conectar.png")).resize((25,25), Image.Resampling.LANCZOS))






###### TELAS DO SISTEMA

frameConexao = tkinter.Frame(janela)
frameConexao.grid_columnconfigure(0, weight=1)
frameConexao.grid(row=0, column=1, sticky="nsew")

frameTelemetria = tkinter.Frame(janela)
frameTelemetria.grid_columnconfigure(2, weight=1)

frameLog = tkinter.Frame(janela)
frameLog.grid_columnconfigure(0, weight=1)

frameNavegacao = tkinter.Frame(janela)
frameNavegacao.grid(row=0, column=0, sticky="nsew")
frameNavegacao.grid_rowconfigure(5, weight=1)





###### Frame de Conexão

statusConexaoLabel = tkinter.Label(frameConexao, bg="red" if statusConexao == False else "green", text="Desconectado" if statusConexao == False else "Conectado", font=fonteBotao)
statusConexaoLabel.grid(row=0, column=0, padx=20, pady=20)

baudRateLabel = tkinter.Label(frameConexao, text="Baud-Rate", font=fonteBotao)
baudRateLabel.grid(row=1, column=0, padx=20, pady=10)


listaBaudRate = ["9600", "38400", "115200"]
varBaudRate = tkinter.StringVar(frameConexao)
varBaudRate.set(listaBaudRate[0])

baudRateSelector = tkinter.OptionMenu(frameConexao, varBaudRate, *listaBaudRate, command=eventoSelectBaudRate)
baudRateSelector.grid(row = 2, column=0, padx=20, pady=10)

portaCOMLabel = tkinter.Label(frameConexao, text="Porta COM", font=fonteBotao)
portaCOMLabel.grid(row=3, column=0, padx=20, pady=0)

varPortaCOM = tkinter.StringVar()
varPortaCOM.set("COM3")

portaCOMSelector = tkinter.OptionMenu(frameConexao, varPortaCOM, value=portList, command=eventoSelectCOM)
portaCOMSelector.grid(row=4, column=0, padx=20, pady=10)

conectarBotao = tkinter.Button(frameConexao, text="Conectar" if statusConexao == False else "Desconectar", image = imagemConectar, command=eventoBotaoConectar)
conectarBotao.grid(row=5, column=0, padx=20, pady=10)

textoRecebido = tkinter.Text(frameConexao, state="normal", font=fonteTexto, width=50, height=10)
textoRecebido.grid(row=6, column=0, padx=20, pady=10)

apagarBotao = tkinter.Button(frameConexao, text="Apagar", image=imagemBorracha, command=eventoBotaoApagar)
apagarBotao.grid(row=7, column=0, padx=20, pady=0)

textoComando = tkinter.Text(frameConexao, state = "disabled" if statusConexao == False else "normal", font=fonteTexto, width=50, height=1)
textoComando.grid(row=8, column=0, padx=20, pady=10)

enviarBotao = tkinter.Button(frameConexao, text="Enviar", state= "disabled" if statusConexao == False else "normal", command=eventoBotaoEnviar)
enviarBotao.grid(row=9, column=0, padx=20, pady=0)





###### Frame De Navegação

frameNavegacaoLogo = tkinter.Label(frameNavegacao, text="", image=imagemLogo, width=200, height=100)
frameNavegacaoLogo.grid(row=0, column=0, padx=20, pady=0)

frameNavegacaoTitulo = tkinter.Label(frameNavegacao, text="Telemetria Imperador", compound="left", font=fonteTitulo)
frameNavegacaoTitulo.grid(row=1, column=0, padx=20, pady=0)

NavegacaoBotaoConexao = tkinter.Button(frameNavegacao, text=" Conexão", font = fonteTitulo, compound=tkinter.LEFT, image=imagemConexao)
NavegacaoBotaoConexao.grid(row=2, column=0, sticky="nsew", padx=10, pady=5)

NavegacaoBotaoTelemetria = tkinter.Button(frameNavegacao, text=" Telemetria", font = fonteTitulo, compound=tkinter.LEFT, image=imagemTelemetria)
NavegacaoBotaoTelemetria.grid(row=3, column=0, sticky="nsew", padx=10, pady=5)

NavegacaoBotaoLog = tkinter.Button(frameNavegacao, text=" Log", font = fonteTitulo, compound=tkinter.LEFT, image=imagemLog)
NavegacaoBotaoLog.grid(row=4, column=0, sticky="nsew", padx=10, pady=5)







janela.mainloop()