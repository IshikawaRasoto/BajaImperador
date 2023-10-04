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
from tkinter import ttk
import os
from PIL import Image, ImageTk
import serial.tools.list_ports # pyserial
import threading
import continuous_threading
import datetime
import numpy
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from drawnow import *
import pandas as pd






###### Variáveis

global portaCOM

portaCOM = 'COM3'

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
temperaturaAtual = True
bateriaAtual = True


dataVel = []
dataRPM = []
dataTempo = []
valoresX = []
fGrafico = Figure(figsize=(7,7), dpi=100)
grafVel = fGrafico.add_subplot(211)
grafRPM = fGrafico.add_subplot(212)

for i in range(0, 60):
    valoresX.append(i)


###### Eventos

def eventoSelectBaudRate(baudRate_recebido):
   
    baudRate_recebido = varBaudRate.get()
    print("Baud Rate recebido: " + baudRate_recebido)

    global baudrate
    baudrate = baudRate_recebido
    print("Variável BaudRate: " + str(baudrate))

    return
    


def eventoSelectCOM(COM_recebido):

    global portaCOM

    COM_recebido = varPortaCOM.get()

    COM_recebido = COM_recebido[2:32]
    
    print("Porta COM recebida: " + COM_recebido)
    
    for i in range(0, len(portList)):
        print(portList[i])
        if portList[i] == COM_recebido:
            print("COM recebida" + portList[i][0:4])
            portaCOM = portList[i][0:4]
            print("Porta COM Selecionada: " + portaCOM)

    return


def eventoBotaoConectar():
    global statusConexao
    global serialInst
    
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
    return

def eventoExportarExcel():
    
    data = {
        'horario': dataTempo,
        'velocidade': dataVel,
        'RPM': dataRPM
    }

    df = pd.DataFrame(data)

    df.to_excel(r'C:\Users\rafae\OneDrive\Documentos\Code\Baja\BajaImperador\2023-2\Telemetria\planilha\data.xlsx', index=False)

    return


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




###### FRAME DE TELEMETRIA

frameTelemetriaEsquerdo = tkinter.Frame(frameTelemetria)
frameTelemetriaEsquerdo.grid_columnconfigure(0, weight=1)
frameTelemetriaEsquerdo.grid(row=0, column=0, sticky="nsew")

frameTelemetriaDireito = tkinter.Frame(frameTelemetria)
frameTelemetriaDireito.grid_columnconfigure(0, weight=1)
frameTelemetriaDireito.grid(row=0, column=1, sticky="nsew")

velocidadeLabel = tkinter.Label(frameTelemetriaEsquerdo, text = "Velocidade: 0 km/h", font=fonteTitulo, image=imagemVelocidade, compound="top")
velocidadeLabel.grid(row=0, column=0, padx=20, pady=20)

rpmLabel = tkinter.Label(frameTelemetriaEsquerdo, text="RPM: 0", font=fonteTitulo, image=imagemRpm, compound="top")
rpmLabel.grid(row=1, column=0, padx=20, pady=5)

rpmProgressBar = ttk.Progressbar(frameTelemetriaEsquerdo, orient="horizontal", length=200)
rpmProgressBar.grid(column=0, row=2, padx=10, pady=0)

temperaturaLabel = tkinter.Label(frameTelemetriaEsquerdo, text="Temperatura", font=fonteTitulo, image=imagemTemperatura, compound="top")
temperaturaLabel.grid(row=3, column=0, padx=20, pady=20)

temperaturaAviso = tkinter.Label(frameTelemetriaEsquerdo, text="OK", font=fonteTitulo, fg="green")
temperaturaAviso.grid(row=4, column=0, padx=20, pady=0)

bateriaLabel = tkinter.Label(frameTelemetriaEsquerdo, text="Bateria", font=fonteTitulo, image=imagemBateria, compound="top")
bateriaLabel.grid(row=5, column=0, padx=20, pady=20)

bateriaAviso = tkinter.Label(frameTelemetriaEsquerdo, text="OK", font=fonteTitulo, fg="green")
bateriaAviso.grid(row=6, column=0, padx=20, pady=0)

freioLabel = tkinter.Label(frameTelemetriaEsquerdo, text=("   Freio: Desativado"), font=fonteTitulo, image=imagemFreio, compound="left")
freioLabel.grid(row=7, column=0, padx=20, pady=50)



###### Frame Log

botaoExportar = tkinter.Button(frameLog, text="Exportar para Excel", command=eventoExportarExcel)
botaoExportar.grid(row=0, column=0, padx=50, pady=100, sticky="we")




###### Funções de Evento do Código

def selecionarFrame(nome):
    
    if nome == "conexao":
        
        frameConexao.grid(row=0, column=1, sticky="nsew")

        global serialInst
        global ports
        global portList

        serialInst = serial.Serial()

        ports = serial.tools.list_ports.comports()
        portList = []

        for onePort in ports:
            portList.append(str(onePort))

        portaCOMSelector = tkinter.OptionMenu(frameConexao, varPortaCOM, value=portList, command=eventoSelectCOM)
        portaCOMSelector.grid(row=4, column=0, padx=20, pady=10)

    else:
        frameConexao.grid_forget()

    
    if nome == "telemetria":
        frameTelemetria.grid(row=0, column=1, sticky="nsew")
    else:
        frameTelemetria.grid_forget()

    if nome == "log":
        frameLog.grid(row=0, column=1, sticky="nsew")
    else:
        frameLog.grid_forget()



def eventoBotaoTelemetria():
    selecionarFrame("telemetria")
    return

def eventoBotaoConexao():
    selecionarFrame("conexao")
    return

def eventoBotaoLog():
    selecionarFrame("log")
    return






###### Threads

def lerSerial():
    
    global textoRecebido
    global velocidadeAtual
    global rpmAtual
    global temperaturaAtual
    global freioAtual
    global bateriaAtual

    if statusConexao == False:
        return
    
    serialTexto = serialInst.readline()

    hoje = datetime.datetime.now()
    horario = hoje.strftime("%H:%M:%S.%f")
    horario = horario[0:11]
    horario_graf = horario[0:8]
    dataTempo.append(horario_graf)

    serialTexto = serialTexto.decode("utf-8")

    texto = serialTexto
    textoRecebido.insert("0.0", horario + " -> " + texto)

    ####

    #velocidadeAtual = int(texto[texto.index("V") + 1: texto.index("T")])
    #dataVel.append(velocidadeAtual)

    #rpmAtual = int(texto[texto.index("R") + 1: texto.index("V")])*10
    #dataRPM.append(rpmAtual)

    #temperatura_string = texto[texto.index("T") + 1: texto.index("F")]
    #freio_string = texto[texto.index("F") + 1: texto.index("B")]
    #bateria_string = texto[texto.index("B") + 1: len(texto) - 1]

    #if temperatura_string == "0":
    #    temperaturaAtual = False
    #else:
    #    temperaturaAtual = True

    #if freio_string == "0":
    #    freioAtual = False
    #else:
    #    freioAtual = True
    
    #if bateria_string == "0":
    #    bateriaAtual = False
    #else:
    #    bateriaAtual = True

    return


def atualizar():

    global textoRecebido
    global velocidadeAtual
    global rpmAtual
    global temperaturaAtual
    global freioAtual
    global bateriaAtual

    print("Thread" + str(temperaturaAtual) + " " + str(bateriaAtual) + " " + str(freioAtual))

    velocidadeLabel.configure(text = ("Velocidade" + str(velocidadeAtual) + " km/h"))
    rpmLabel.configure(text=("RPM" + str(rpmAtual)))
    rpmProgressBar['value'] = (rpmAtual/4000)*100

    if temperaturaAtual == True:
        temperaturaAviso.configure(fg="red", text="ALERTA - ALTA")
    else:
        temperaturaAviso.configure(fg="green", text="OK")

    if bateriaAtual == True:
        bateriaAviso.configure(fg="red", text="Alerta")
    else:
        bateriaAviso.configure(fg="green", text="OK")

    if freioAtual == True:
        freioLabel.configure(text="   Freio: Ativado")
    else:
        freioLabel.configure(text = "   Freio: Desativado")

    return


def animacaoGraficos():

    dataVelGrafico = dataVel[-60:]
    dataRPMGrafico = dataRPM[-60:]

    grafVel.clear()
    grafRPM.clear()

    grafVel.plot(valoresX, dataVelGrafico, 'b')
    grafRPM.plot(valoresX, dataRPMGrafico, 'b')

    grafVel.set_title("Velocidade")
    grafRPM.set_title("RPM")

    grafVel.set_ylabel("km/h")
    grafVel.set_xlabel("s")
    grafVel.set_xlim(0, 60)
    grafVel.set_ylim(0, 55)

    grafRPM.set_ylabel("RPM")
    grafRPM.set_xlabel("s")
    grafRPM.set_xlim(0, 60)
    grafRPM.set_ylim(0, 4500)

    return


###### Frame De Navegação

frameNavegacaoLogo = tkinter.Label(frameNavegacao, text="", image=imagemLogo, width=200, height=100)
frameNavegacaoLogo.grid(row=0, column=0, padx=20, pady=0)

frameNavegacaoTitulo = tkinter.Label(frameNavegacao, text="Telemetria Imperador", compound="left", font=fonteTitulo)
frameNavegacaoTitulo.grid(row=1, column=0, padx=20, pady=0)

NavegacaoBotaoConexao = tkinter.Button(frameNavegacao, text=" Conexão", font = fonteTitulo, compound=tkinter.LEFT, image=imagemConexao, command=eventoBotaoConexao)
NavegacaoBotaoConexao.grid(row=2, column=0, sticky="nsew", padx=10, pady=5)

NavegacaoBotaoTelemetria = tkinter.Button(frameNavegacao, text=" Telemetria", font = fonteTitulo, compound=tkinter.LEFT, image=imagemTelemetria, command=eventoBotaoTelemetria)
NavegacaoBotaoTelemetria.grid(row=3, column=0, sticky="nsew", padx=10, pady=5)

NavegacaoBotaoLog = tkinter.Button(frameNavegacao, text=" Log", font = fonteTitulo, compound=tkinter.LEFT, image=imagemLog, command=eventoBotaoLog)
NavegacaoBotaoLog.grid(row=4, column=0, sticky="nsew", padx=10, pady=5)


###### Gráficos


graficos = FigureCanvasTkAgg(fGrafico, master=frameTelemetriaDireito)
graficos.draw()
graficos.get_tk_widget().pack(side=tkinter.BOTTOM, fill=tkinter.BOTH, expand = False)
graficos._tkcanvas.pack()
graficos._tkcanvas.pack(side=tkinter.TOP, fill=tkinter.BOTH, expand = False)

ani = FuncAnimation(fGrafico, animacaoGraficos, interval=250, blit=False)







###### Declaração das Threads

threadSerial = continuous_threading.PeriodicThread(0.5, lerSerial)
threadAtualizar = continuous_threading.PeriodicThread(0.5, atualizar)
threadSerial.start()
threadAtualizar.start()



janela.mainloop()

threadSerial.stop()
threadAtualizar.stop()