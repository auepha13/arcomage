/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package clientserver;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import javax.swing.text.JTextComponent;

/**
 *
 * @author SF
 */
public abstract class BasicServer
{

  private final int PORTNR;
  private JTextComponent taLog;
  private ServerThread st;

  public BasicServer()
  {
    PORTNR = 9999;
  }

  public BasicServer(int portnr)
  {
    this.PORTNR = portnr;
  }

  public BasicServer(int portnr, JTextComponent taLog)
  {
    this(portnr);
    this.taLog = taLog;
    
  }

  protected void log(String message)
  {
    if (taLog != null)
    {
      taLog.setText(taLog.getText() + "\n" + message);
    } else
    {
        System.out.println(message);
    }
  }

  public void startServer()
  {
    if ((st == null) || (!st.isAlive()))
    {
      try
      {
        st = new ServerThread();
        st.start();
      } catch (IOException ex)
      {
        st = null;
        log("Starting server failed");
      }
    }
  }

  public void stopServer()
  {
    if ((st != null) && (st.isAlive()))
    {
      st.interrupt();
    }
  }

  class ServerThread extends Thread
  {

    private final ServerSocket serverSocket;

    public ServerThread() throws IOException
    {
      serverSocket = new ServerSocket(PORTNR);
      log("Server started on port: " + PORTNR);
      serverSocket.setSoTimeout(250);
    }

    @Override
    public void run()
    {
      while (!interrupted())
      {
        try
        {
          Socket socket = serverSocket.accept();
          log("Connected to " + socket.getRemoteSocketAddress());
          new ClientCommunicationThread(socket);
        } catch (SocketTimeoutException ex)
        {
//          log("timeout");
        } catch (IOException ex)
        {
          log("Connection failed");
        }
      }
      try
      {
        serverSocket.close();
      } catch (IOException ex)
      {
        log("Closing server failed");
      }
      log("Server shutdown");
    }
  }

  class ClientCommunicationThread extends Thread
  {

    private Socket socket;

    public ClientCommunicationThread(Socket socket) throws SocketException
    {
      this.socket = socket;
      this.socket.setSoTimeout(1000);
      start();
    }

    @Override
    public void run()
    {
      try (ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
          ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream()))
      {
        Object request = ois.readObject();
        oos.writeObject(processRequest(request));
      } catch (IOException | ClassNotFoundException ex)
      {
        log("Error in ClientCommunicationThread " + ex.toString());
      }
      log("request finished " + socket.getRemoteSocketAddress());
    }
  }

  protected abstract Object processRequest(Object request);

}
