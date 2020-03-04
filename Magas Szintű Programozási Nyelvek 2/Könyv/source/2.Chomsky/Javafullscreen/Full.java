import java.awt.Frame;
import java.awt.Graphics;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Window;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;

import javax.imageio.ImageIO;
 class FULLOS extends Window
{

  private BufferedImage pic;

  public static void main(String[] args) {
    GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
    GraphicsDevice screen = ge.getDefaultScreenDevice();

    if (!screen.isFullScreenSupported()) {
      System.out.println("A teljes képernyős kijelzés nincs támogatva!");
      System.exit(1);
    }

    try {
      BufferedImage loadedpic = ImageIO.read(new File("pic.jpg"));
      screen.setFullScreenWindow(new FULLOS(loadedpic));
    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }

  public FULLOS(BufferedImage pic) {
    super(new Frame());

    this.pic = pic;

    addMouseListener(new MouseAdapter() {
      public void mouseClicked(MouseEvent e) {
        System.exit(0);
      }
    }
);
  }

  public void paint(Graphics g) {
    g.drawImage(pic, 0, 0, getWidth(), getHeight(), this);
  }
}
