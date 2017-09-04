describe "awesome shell" do
  it "can execute `ls`" do
    dir_listing = execute_command("ls")

    expect(dir_listing).to include("README.md")
    expect(dir_listing).to include("src")
    expect(dir_listing).to include("specs")
  end

  # executes a command in awesome shell
  def execute_command(cmd)
    raw_output = nil

    IO.popen("./shell", "r+") do |pipe|
      pipe.puts cmd
      pipe.close_write
      raw_output = pipe.gets(nil)
    end

    raw_output
  end
end
