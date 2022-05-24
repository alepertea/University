using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Lab1
{
    public partial class Form1 : Form
    {
        SqlConnection connection = new SqlConnection(@"Data Source=DESKTOP-IKRGGHC\SQLEXPRESS;Database=PetStore;Integrated Security=true");
        SqlDataAdapter dataAdapterMagazin = new SqlDataAdapter();
        DataSet dataSetMagazin = new DataSet();
        SqlDataAdapter dataAdapterAngajat = new SqlDataAdapter();
        DataSet dataSetAngajat = new DataSet();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                dataAdapterMagazin.SelectCommand = new SqlCommand("SELECT * FROM Magazin", connection);
                dataSetMagazin.Clear();
                dataAdapterMagazin.Fill(dataSetMagazin);
                dataGridView_Magazin.DataSource = dataSetMagazin.Tables[0];
            }catch(Exception ex)
            {
                messageToUser.Text += ex.Message;
                messageToUser.ForeColor = Color.DarkRed;
                connection.Close();
            }
            
            stergereButton.Visible = false;
            actualizareButton.Visible = false;
            adaugareButton.Visible = false;
            magazinIdTextBox.Enabled = false; denumireTextBox.Enabled = false; numarOraseTextBox.Enabled = false; 
            idAngajatTextBox.Enabled = false; idMagazinTextBox.Enabled = false;
        }

        private void dataGridView_Magazin_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            stergereButton.Visible = false;
            actualizareButton.Visible = false;
            adaugareButton.Visible = true;
            prenumeTextBox.Enabled = true;
            messageToUser.Text = "";
            idAngajatTextBox.Text = ""; numeTextBox.Text = ""; prenumeTextBox.Text = ""; dataNasteriiTextBox.Text = ""; observatiiTextBox.Text = "";

            try
            {
                if (dataGridView_Magazin.Rows[e.RowIndex].Cells[e.ColumnIndex].Value != null)
                {
                    dataGridView_Magazin.CurrentRow.Selected = true;

                    magazinIdTextBox.Text = dataGridView_Magazin.Rows[e.RowIndex].Cells["idMagazin"].FormattedValue.ToString();
                    denumireTextBox.Text = dataGridView_Magazin.Rows[e.RowIndex].Cells["denumire"].FormattedValue.ToString();
                    numarOraseTextBox.Text = dataGridView_Magazin.Rows[e.RowIndex].Cells["numarOrase"].FormattedValue.ToString();

                    idMagazinTextBox.Text = magazinIdTextBox.Text;

                    dataAdapterAngajat.SelectCommand = new SqlCommand("SELECT * FROM Angajat WHERE idMagazin = @idMagazin", connection);
                    dataAdapterAngajat.SelectCommand.Parameters.AddWithValue("@idMagazin", magazinIdTextBox.Text);
                    dataSetAngajat.Clear();
                    dataAdapterAngajat.Fill(dataSetAngajat);
                    dataGridView_Angajat.DataSource = dataSetAngajat.Tables[0];
                }
            }
            catch(Exception ex)
            {
                connection.Close();
                messageToUser.Text = ex.Message;
                messageToUser.ForeColor = Color.DarkRed;
            }
        }

        private void dataGridView_Angajat_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            messageToUser.Text = "";
            adaugareButton.Visible = false;
            stergereButton.Visible = true;
            actualizareButton.Visible = true;
            prenumeTextBox.Enabled = false;

            try
            {
                if (dataGridView_Angajat.Rows[e.RowIndex].Cells[e.ColumnIndex].Value != null)
                {
                    dataGridView_Angajat.CurrentRow.Selected = true;

                    idAngajatTextBox.Text = dataGridView_Angajat.Rows[e.RowIndex].Cells["idAngajat"].FormattedValue.ToString();
                    idMagazinTextBox.Text = dataGridView_Angajat.Rows[e.RowIndex].Cells["idMagazin"].FormattedValue.ToString();
                    numeTextBox.Text = dataGridView_Angajat.Rows[e.RowIndex].Cells["nume"].FormattedValue.ToString();
                    prenumeTextBox.Text = dataGridView_Angajat.Rows[e.RowIndex].Cells["prenume"].FormattedValue.ToString();
                    dataNasteriiTextBox.Text = dataGridView_Angajat.Rows[e.RowIndex].Cells["dataNasterii"].FormattedValue.ToString();
                    observatiiTextBox.Text = dataGridView_Angajat.Rows[e.RowIndex].Cells["observatii"].FormattedValue.ToString();
                }
            }catch(Exception ex)
            {
                messageToUser.Text = ex.Message;
                messageToUser.ForeColor = Color.DarkRed;
            }
        }

        private void stergereButton_Click(object sender, EventArgs e)
        {
            try
            {
                string idAngajat = dataGridView_Angajat.SelectedRows[0].Cells["idAngajat"].FormattedValue.ToString();

                dataAdapterAngajat.DeleteCommand = new SqlCommand("DELETE FROM Angajat WHERE idAngajat = @idAngajat", connection);
                dataAdapterAngajat.DeleteCommand.Parameters.AddWithValue("@idAngajat", idAngajat);

                connection.Open();
                dataAdapterAngajat.DeleteCommand.ExecuteNonQuery();
                connection.Close();

                messageToUser.Text = "Angajat sters cu succes!";
                messageToUser.ForeColor = Color.DarkGreen;

                dataSetAngajat.Clear();
                dataAdapterAngajat.Fill(dataSetAngajat);
            }catch(Exception ex)
            {
                connection.Close();
                messageToUser.Text = ex.Message;
                messageToUser.ForeColor = Color.DarkRed;
            }
        }

        private void actualizareButton_Click(object sender, EventArgs e)
        {
            try
            {
                if(numeTextBox.Text == "" || dataNasteriiTextBox.Text == "")
                {
                    throw new Exception("Actualizarea nu s-a putut efectua!\nCampurile nu pot fi goale! (exceptie: Observatii)!");
                }

                dataAdapterAngajat.UpdateCommand = new SqlCommand("UPDATE Angajat SET nume = @nume, dataNasterii = @dataNasterii, observatii = @observatii" +
                    " WHERE idAngajat = @idAngajat", connection);
                dataAdapterAngajat.UpdateCommand.Parameters.AddWithValue("@nume", numeTextBox.Text);
                dataAdapterAngajat.UpdateCommand.Parameters.AddWithValue("@idAngajat", idAngajatTextBox.Text);
                dataAdapterAngajat.UpdateCommand.Parameters.AddWithValue("@observatii", observatiiTextBox.Text);
                dataAdapterAngajat.UpdateCommand.Parameters.AddWithValue("@dataNasterii", dataNasteriiTextBox.Text);

                connection.Open();
                dataAdapterAngajat.UpdateCommand.ExecuteNonQuery();
                connection.Close();

                dataSetAngajat.Clear();
                dataAdapterAngajat.Fill(dataSetAngajat);

                messageToUser.Text = "Angajat actualizat cu succes!";
                messageToUser.ForeColor = Color.DarkGreen;
            }
            catch(Exception ex)
            {
                connection.Close();
                messageToUser.Text = ex.Message;
                messageToUser.ForeColor = Color.DarkRed;
            }
        }

        private void adaugareButton_Click(object sender, EventArgs e)
        {
            try
            {
                if(numeTextBox.Text == "" || prenumeTextBox.Text == "" || dataNasteriiTextBox.Text == "")
                {
                    throw new Exception("Adaugarea nu s-a putut efectua!\nCampurile nu pot fi goale! (exceptie: Observatii)");
                }

                dataAdapterAngajat.InsertCommand = new SqlCommand("INSERT INTO Angajat(idMagazin, nume, prenume, dataNasterii, observatii) " +
                    "VALUES (@idMagazin, @nume, @prenume, @dataNasterii, @observatii)", connection);
                dataAdapterAngajat.InsertCommand.Parameters.AddWithValue("@idMagazin", idMagazinTextBox.Text);
                dataAdapterAngajat.InsertCommand.Parameters.AddWithValue("@nume", numeTextBox.Text);
                dataAdapterAngajat.InsertCommand.Parameters.AddWithValue("@prenume", prenumeTextBox.Text);
                dataAdapterAngajat.InsertCommand.Parameters.AddWithValue("@dataNasterii", dataNasteriiTextBox.Text);
                dataAdapterAngajat.InsertCommand.Parameters.AddWithValue("@observatii", observatiiTextBox.Text);

                connection.Open();
                dataAdapterAngajat.InsertCommand.ExecuteNonQuery();
                connection.Close();

                dataSetAngajat.Clear();
                dataAdapterAngajat.Fill(dataSetAngajat);

                messageToUser.Text = "Angajat adăugat cu succes!";
                messageToUser.ForeColor = Color.DarkGreen;
            }
            catch(Exception ex)
            {
                connection.Close();
                messageToUser.Text = ex.Message;
                messageToUser.ForeColor = Color.DarkRed;
            }
        }
    }
}
