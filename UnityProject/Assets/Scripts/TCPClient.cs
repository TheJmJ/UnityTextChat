using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;
using UnityEngine.UI;

public class TCPClient : MonoBehaviour
{
    private TcpClient socketConnection;
    private Thread clientReceiveThread;
    public string[] chatText = new string[15];

    void AddToChat(string s)
    {
        for(int i = (chatText.Length - 1); i > 0;)
        {
            chatText[i] = chatText[--i];
        }
        chatText[0] = s;
    }

    private void Start()
    {
        ConnectToTCPServer();
    }

    private void ConnectToTCPServer()
    {
        try
        {
            clientReceiveThread = new Thread(new ThreadStart(ListenForData));
            clientReceiveThread.IsBackground = true;
            clientReceiveThread.Start();
            chatText[0] = "Connecting....";
        }
        catch(Exception e)
        {
            Debug.LogError("On client connect exception " + e);
        }
    }

    private void ListenForData()
    {
        socketConnection = new TcpClient("localhost", 2310);
        Byte[] bytes = new byte[1024];
        chatText[0] = "Connected!";
        while (true)
        {
            // Get stream for reading
            using (NetworkStream stream = socketConnection.GetStream())
            {
                int length;

                while((length = stream.Read(bytes,0,bytes.Length))!= 0)
                {
                    var incomingData = new byte[length];
                    Array.Copy(bytes, 0, incomingData, 0, length);

                    string serverMessage = Encoding.ASCII.GetString(incomingData);
                    AddToChat(serverMessage);
                    Debug.Log("Got message");
                }
            }
        }
    }

    [ContextMenu("Send Test Message")]
    public void _SendMessage(string msg = "This is a message from one of your clients.")
    {
        if(socketConnection == null)
        {
            Debug.LogWarning("No Socketconnection");
            return;
        }
        try
        {
            // Get a stream object for writing. 			
            NetworkStream stream = socketConnection.GetStream();
            if (stream.CanWrite)
            {
                string clientMessage = msg;
                // Convert string message to byte array.
                byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage);
                // Write byte array to socketConnection stream.                 
                stream.Write(clientMessageAsByteArray, 0, clientMessageAsByteArray.Length);
                Debug.Log("Client sent his message - should be received by server");
            }
        }
        catch (SocketException socketException)
        {
            Debug.Log("Socket exception: " + socketException);
        }
    }
    private void OnDestroy()
    {
        clientReceiveThread.Abort();
    }
}
