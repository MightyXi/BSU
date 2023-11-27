import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Size;
import org.opencv.core.CvType;
import org.opencv.core.Scalar;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;


public class Frame extends JFrame {

    File file;
    int count = 0;
    Frame(){

        JFrame jFrame = new JFrame();

        JButton open = new JButton("open");
        JButton apply1 = new JButton("apply1");
        JButton apply2 = new JButton("apply2");

        jFrame.setLayout(new FlowLayout());

        jFrame.setSize(1700, 1200);
        JLabel jLabel = new JLabel();
        JLabel jLabel2 = new JLabel();
        JLabel jLabel3 = new JLabel();
        JLabel jLabel4 = new JLabel();


        jFrame.add(open);
        jFrame.add(apply1);
        jFrame.add(apply2);
        jFrame.add(jLabel);
        jFrame.add(jLabel2);
        jFrame.add(jLabel3);
        jFrame.add(jLabel4);
        jFrame.setVisible(true);


        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


        open.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser("C:\\Users\\lenovo\\Desktop\\images");
                int retValue = fileChooser.showOpenDialog(Frame.this);
                if (retValue == JFileChooser.APPROVE_OPTION){
                    file = fileChooser.getSelectedFile();
                    try{
                        BufferedImage buf = ImageIO.read(file);
                        ImageIcon imageIcon = new ImageIcon(buf.getScaledInstance(400, 400, Image.SCALE_DEFAULT));
                        jLabel.setIcon(imageIcon);
                    } catch (IOException ex){
                        JOptionPane.showMessageDialog(null, "Error:" + ex.getMessage());
                    }
                }
            }
        });

        apply1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Mat image = Imgcodecs.imread(file.getAbsolutePath());

                // Создание пустой матрицы для результата
                Mat smoothedImage = new Mat(image.rows(), image.cols(), CvType.CV_8UC3);

                // Применение сглаживающего фильтра
                Imgproc.blur(image, smoothedImage, new Size(10, 10));

                // Преобразование Mat в BufferedImage
                Imgcodecs.imwrite("C:\\Users\\lenovo\\Desktop\\temp\\" + count + ".jpg", smoothedImage);
                File temp = new File("C:\\Users\\lenovo\\Desktop\\temp\\" + count + ".jpg");
                count++;
                try{
                    BufferedImage buf = ImageIO.read(temp);
                    ImageIcon imageIcon = new ImageIcon(buf.getScaledInstance(400, 400, Image.SCALE_DEFAULT));
                    jLabel2.setIcon(imageIcon);
                    jLabel3.setIcon(null);
                    jLabel4.setIcon(null);
                }catch (IOException ex){
                    JOptionPane.showMessageDialog(null, "Error:" + ex.getMessage());
                }
            }
        });

        apply2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Mat image = Imgcodecs.imread(file.getAbsolutePath());

                // Преобразование изображения в оттенки серого
                Mat grayImage = new Mat();
                Imgproc.cvtColor(image, grayImage, Imgproc.COLOR_BGR2GRAY);

                // Применение локальной пороговой обработки с методом Otsu
                Mat bernsonThresholdedImage = new Mat();
                Imgproc.adaptiveThreshold(grayImage, bernsonThresholdedImage, 255, Imgproc.ADAPTIVE_THRESH_MEAN_C ,Imgproc.THRESH_BINARY, 15, 15);

                // Применение локальной пороговой обработки с методом Нилбека
                int blockSize = 25;
                double k = 0.8;

                // Применение метода Нилбека без вынесения методов в отдельные функции
                Mat localMean = new Mat();
                Imgproc.blur(grayImage, localMean, new Size(blockSize, blockSize));
                Mat result = new Mat();
                Core.add(localMean, new Scalar(k), result);
                Core.compare(grayImage, result, result, Core.CMP_GT);
                Core.multiply(result, new Scalar(255), result);

                Mat adaptiveThresholdedImage = new Mat();
                Imgproc.adaptiveThreshold(grayImage, adaptiveThresholdedImage, 255, Imgproc.ADAPTIVE_THRESH_MEAN_C, Imgproc.THRESH_BINARY, 11, 2);


                // Сохранение результатов
                Imgcodecs.imwrite("C:\\Users\\lenovo\\Desktop\\temp\\" + count + "1.jpg", bernsonThresholdedImage);
                Imgcodecs.imwrite("C:\\Users\\lenovo\\Desktop\\temp\\" + count + "2.jpg", result);
                Imgcodecs.imwrite("C:\\Users\\lenovo\\Desktop\\temp\\" + count + "3.jpg", adaptiveThresholdedImage);

                //File temp1 = new File("C:\\Users\\lenovo\\Desktop\\temp\\" + count + "1.jpg");
                File temp2 = new File("C:\\Users\\lenovo\\Desktop\\temp\\" + count + "2.jpg");
                File temp3 = new File("C:\\Users\\lenovo\\Desktop\\temp\\" + count + "3.jpg");
                count++;
                try{
                    //BufferedImage buf1 = ImageIO.read(temp1);
                    BufferedImage buf2 = ImageIO.read(temp2);
                    BufferedImage buf3 = ImageIO.read(temp3);
                    //ImageIcon imageIcon1 = new ImageIcon(buf1.getScaledInstance(400, 400, Image.SCALE_DEFAULT));
                    //jLabel2.setIcon(imageIcon1);
                    ImageIcon imageIcon2 = new ImageIcon(buf2.getScaledInstance(400, 400, Image.SCALE_DEFAULT));
                    jLabel3.setIcon(imageIcon2);
                    ImageIcon imageIcon3 = new ImageIcon(buf3.getScaledInstance(400, 400, Image.SCALE_DEFAULT));
                    jLabel4.setIcon(imageIcon3);
                }catch (IOException ex){
                    JOptionPane.showMessageDialog(null, "Error:" + ex.getMessage());
                }
            }
        });
    }

    public static void main(String[] args) throws IOException{
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
        Frame base = new Frame();
        base.setSize(1000, 700);
    }
}